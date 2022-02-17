// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include "SimpleCanonMovMaker.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace myapp {

/*
 * 'timelapse' takes pictures following given parameters and makes a video,
 * 'stitch' allows u to create a video from your session,
 * 'camera' allows you to take pictures only"
 */
DEFINE_string(mode, "camera", "The desired mode: camera, stitch, or timelapse");
DEFINE_uint32(interval, 10,
              "The desired interval in seconds between pictures (min 3).");
DEFINE_uint32(num_of_pics, 5,
              "The desired number of pictures to take total (min 1).");
// vid_length not currently implemented
DEFINE_uint32(vid_length, 15,
              "The desired length of the video in seconds (min 3).");
DEFINE_uint32(fps, 60, "Framerate for live view");

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "Simple Canon Movie Maker. Pass in args to specify/config mode");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("SimpleMovieMaker for Canon");
  if (FLAGS_fps > 0) {
    settings->setFrameRate(FLAGS_fps);
  } else {
    settings->setFrameRate(30);
  }
}

}  // namespace myapp

// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
