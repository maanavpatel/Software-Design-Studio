// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <fstream>
#include <iostream>

#include "CanonCamera.h"
#include "CinderCanon.h"
#include "cinder/Timeline.h"
#include "cinder/Utilities.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"

using namespace ci;
namespace myapp {

enum class Mode { timelapse, camera, stitch };

class MyApp : public cinder::app::App, public canon::PhotoHandler {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void takePhoto();

  // Handle callbacks from canon::PhotoHandler
  void photoTaken(EdsDirectoryItemRef directoryItem, EdsError error) override;
  void photoDownloaded(const std::string& downloadPath,
                       EdsError error) override;
  std::string photoDownloadDirectory() override;

 private:
  /**
   * Creates a .avi video from all .JPG photos taken during a session.
   */
  void MakeVideo();
  /**
   * Object representing a connected Canon Camera.
   */
  CanonCamera mCamera;
  /**
   * Folder where photos from session will be downloaded.
   */
  fs::path mPhotoDownloadFolder;
  Anim<float> mFlashAlpha;
  /**
   * Framerate of video.
   */
  const size_t kFramrate = 30;
  // Framerate is currently fixed value because of file size issues
  /**
   * How often to taken pictures. (In seconds)
   */
  size_t interval_s_;
  /**
   * User defined number of picture to be taken during timelapse
   */
  size_t num_of_pics_;
  size_t vid_length_;  // TODO: add logic to have vid_length_ customizable;
  /**
   * The number of pictures taken during timelapse
   * (extra pictures taken manually do not count towards number for timelapse).
   */
  size_t shutter_count_ = 0;
  /**
   * How long each picture will be shown for in the video.
   * timelapse = 1.0s, stitch = 3.0s
   */
  double mPictureDuration;
  /**
   * Generates a name for the download folder based on current date and time.
   * @return folder name
   */
  string GetDownloadFolderName();
  /**
   * Tracks the mode the user has selected using gflags. Will default to camera
   */
  Mode mode = Mode::camera;
  /**
   * Used to keep track of time intervals for use with timelapse
   */
  std::chrono::time_point<std::chrono::system_clock> last_time_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
