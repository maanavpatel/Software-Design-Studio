// Copyright (c) 2020 Maanav Patel. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <cstdlib>
#include <iostream>
#include <string>

DEFINE_string(train, "", "model name");
DEFINE_string(model, "", "model path");
DEFINE_string(images, "", "file path for images");
DEFINE_string(labels, "", "file path to labels for the images");
using bayes::Classifier;
using bayes::Image;
using bayes::Model;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<Image> CreateVecOfImages(std::ifstream& images_file,
                                std::ifstream& labels) {
  // a vector of all Image objects created from the file
  vector<Image> allImages;
  // Will hold kImageSize lines worth of strings so that an
  // Image can be made from it
  vector<string> image_strings;

  string line;
  size_t line_count = 0;
  while (std::getline(images_file, line)) {
    // every kImageSize lines make an Image and push to vector
    if (line_count != 0 && line_count % (bayes::kImageSize) == 0) {
      // label for the image
      string label;
      std::getline(labels, label);
      // each label is just 1 char between '0'-'9'
      char label_char = label[0];
      Image i(image_strings, label_char);
      // add the image to the list
      allImages.push_back(i);
      image_strings.clear();
    }
    if (line.length() == bayes::kImageSize) {
      image_strings.push_back(line);
    } else {
      cout << "invalid image file" << endl;
      break;
    }
    ++line_count;
  }

  // have to repeat one last time once file has reached end
  string label;
  std::getline(labels, label);
  char label_char = label[0];
  Image i(image_strings, label_char);
  allImages.push_back(i);
  image_strings.clear();

  return allImages;
}

int Train() {
  cout << FLAGS_train << endl;
  cout << FLAGS_images << endl;
  cout << FLAGS_labels << endl;

  std::ifstream training_images(FLAGS_images);
  std::ifstream training_labels(FLAGS_labels);

  if (training_images.fail()) {
    cout << "Something is wrong with the file path for images" << endl;
    return EXIT_FAILURE;
  } else if (training_labels.fail()) {
    cout << "Something is wrong with the file path for labels." << endl;
    return EXIT_FAILURE;
  } else {
    // after creating this vector it is only passed/used by reference
    vector<Image> all_images =
        CreateVecOfImages(training_images, training_labels);
    Model model(all_images, FLAGS_train);
    model.MakeJson();
  }
  return EXIT_SUCCESS;
}

int Classify() {
  std::ifstream images(FLAGS_images);
  std::ifstream labels(FLAGS_labels);
  std::ifstream model(FLAGS_model);
  if (images.fail()) {
    cout << "Something is wrong with the file path for images" << endl;
    return EXIT_FAILURE;
  } else if (labels.fail()) {
    cout << "Something is wrong with the file path for labels." << endl;
    return EXIT_FAILURE;
  } else if (model.fail()) {
    cout << "Something is wrong with the file path for model." << endl;
    return EXIT_FAILURE;
  } else {
    vector<Image> all_images = CreateVecOfImages(images, labels);
    Classifier classifier(FLAGS_model, all_images);
    classifier.Classify();
    //    classifier.PrintClassifications();
    cout << classifier.GetAccuracy() * 100 << '%' << endl;
  }
  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  gflags::SetUsageMessage("Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (!FLAGS_train.empty()) {
    Train();
  } else if (!FLAGS_model.empty()) {
    Classify();
  } else {
    cout << "Invalid arguments" << endl;
  }
  return EXIT_SUCCESS;
}
