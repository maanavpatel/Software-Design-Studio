// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "SimpleCanonMovMaker.h"

#include <cinder/app/App.h>
#include <gflags/gflags.h>

#include "CanonCamera.h"
#include "CinderCanon.h"

namespace myapp {
DECLARE_string(mode);
DECLARE_uint32(interval);
DECLARE_uint32(num_of_pics);
DECLARE_uint32(vid_length);

using cinder::app::KeyEvent;
using namespace cv;

MyApp::MyApp()
    : interval_s_{FLAGS_interval},
      num_of_pics_{FLAGS_num_of_pics},
      vid_length_{FLAGS_vid_length} {}

void MyApp::setup() {
  if (toLowerCase(FLAGS_mode) == "timelapse") {
    mode = Mode::timelapse;
    cout << "MODE: timelapse" << endl;
  } else if (toLowerCase(FLAGS_mode) == "stitch") {
    mode = Mode::stitch;
    cout << "MODE: stitch" << endl;
  } else {
    cout << "MODE: camera" << endl;
    // will default to camera if other two cases not met
  }
  // reset values if not large enough
  if (interval_s_ < 3) {
    interval_s_ = 3;
  }
  if (vid_length_ < 3) {
    vid_length_ = 3;
  }
  if (num_of_pics_ < 1) {
    num_of_pics_ = 1;
  }
  mFlashAlpha = 0.0f;
  string folder = GetDownloadFolderName();
  mPhotoDownloadFolder =
      getHomeDirectory() / "Documents/DEV" / "Canon Pictures" / folder;
  if (!fs::exists(mPhotoDownloadFolder))
    fs::create_directories(mPhotoDownloadFolder);
  mCamera.setup();
  if (mCamera.getCannon().getNumConnectedCameras() == 0) {
    cerr << "No cameras connected" << endl;
    quit();
  } else {
    mCamera.startLiveView();
  }
  if (mode == Mode::stitch) {
    mPictureDuration = 3.0;
  } else {
    mPictureDuration = 0.8;
  }
}

string MyApp::GetDownloadFolderName() {
  // creates a name for the folder with the current date and time
  time_t now = time(nullptr);
  tm* ltm = localtime(&now);
  stringstream ss;
  ss << 1900 + ltm->tm_year << "_" << 1 + ltm->tm_mon << "_" << ltm->tm_mday;
  ss << "_" << 1 + ltm->tm_hour << 1 + ltm->tm_min << 1 + ltm->tm_sec;
  return ss.str();
}

void MyApp::update() {
  const auto time = std::chrono::system_clock::now();
  if (mode == Mode::timelapse) {
    // give a 5 second delay,
    // then check if its been interval_ seconds since last picture
    // keeps going until the target num_of_pics has been met
    if (getElapsedSeconds() > 5.0 &&
        time - last_time_ > std::chrono::milliseconds(interval_s_ * 1000) &&
        shutter_count_ < num_of_pics_) {
      last_time_ = time;
      takePhoto();
      ++shutter_count_;
      cout << "Photo taken --- " << shutter_count_
           << "===" << getElapsedSeconds() << std::endl;
    }
    // 5 second delay to allow picture to download
    if (time - last_time_ > std::chrono::milliseconds(5000) &&
        shutter_count_ == num_of_pics_) {
      mCamera.endLiveView();
      MakeVideo();
      quit();
    }
  }
  mCamera.update();
}

void MyApp::draw() {
  gl::enableAlphaBlending();
  gl::clear(Color::black());
  if (mCamera.isLiveViewing()) {
    mCamera.draw(getWindowBounds());
  }
  if (mFlashAlpha > 0.0f) {
    gl::color(1.0f, 1.0f, 1.0f, mFlashAlpha);
    gl::drawSolidRect(getWindowBounds());
  }
}

void MyApp::takePhoto() {
  mCamera.endLiveView();
  mCamera.takePicture(this);
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getChar()) {
    case 'l':
      mCamera.toggleLiveView();
      break;
    case 'f':
      setFullScreen(!isFullScreen());
      break;
    case ' ':
      takePhoto();
      std::cout << mCamera.getCapturedFrames().size() << std::endl;
      break;
    case event.KEY_ESCAPE:
      mCamera.endLiveView();
      if (mode == Mode::stitch) {
        MakeVideo();
      }
      quit();
      break;
  }
}

void MyApp::MakeVideo() {
  cout << "Making Video" << endl;
  // select only jpg in path
  string type = "/*.JPG";
  string path = mPhotoDownloadFolder.string() + type;
  vector<string> file_names;
  // recursively fills file_names with all .jpg in the directory
  cv::glob(path, file_names, true);
  if (!file_names.empty()) {
    Mat image = imread(file_names[0]);
    stringstream video_name;
    // TODO: find a more compressed format for output as output
    // file sizes are currently very large (500MB+)
    video_name << mPhotoDownloadFolder.generic_string() << ".avi";
    // Define the codec and create VideoWriter object.
    VideoWriter video(video_name.str(), VideoWriter::fourcc('M', 'J', 'P', 'G'),
                      kFramrate,
                      cv::Size(image.size().width, image.size().height));
    // iterate through each picture
    for (size_t i = 0; i < file_names.size(); ++i) {
      Mat img = imread(file_names[i]);
      if (img.empty()) {
        break;
      }
      cout << "writing: " << file_names[i] << endl;
      for (size_t k = 0; k < mPictureDuration * kFramrate; ++k) {
        video.write(img);
      }
      cout << "finished writing: " << file_names[i] << endl;
    }
    cout << "all images written" << endl;
  } else {
    cerr << "No Pictures Found" << endl;
  }
}

#pragma mark
#pragma mark Callbacks from the canon SDK
//-----------------------------------------------------------------------------------

void MyApp::photoTaken(EdsDirectoryItemRef directoryItem, EdsError error) {
  mCamera.downloadImage(directoryItem, this);
}

void MyApp::photoDownloaded(const std::string& downloadPath, EdsError error) {
  mCamera.startLiveView();
}

// Delegate method to tell the canon where to download the full-res image.
std::string MyApp::photoDownloadDirectory() {
  return mPhotoDownloadFolder.generic_string();
}

}  // namespace myapp
