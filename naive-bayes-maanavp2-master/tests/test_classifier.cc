// Copyright (c) 2020 Maanav Patel. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <bayes/classifier.h>
#include <bayes/utils.h>

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("Classifier", "[classifier]") {
  // have to use test... files because the sample files given are not
  // properly formatted.
  std::ifstream images(
      "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/testimages");
  std::ifstream labels(
      "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/testlabels");

  if (images.fail() || labels.fail()) {
    cout << "check image or label file";
  } else {
    string model_path =
        "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/MyModel.json";
    std::vector<bayes::Image> all_images =
        bayes::CreateVecOfImages(images, labels);

    SECTION("CreateVecOfImages") {
      // only three images in sample files
      REQUIRE(all_images.size() == 1000);
    }

    SECTION("Classify on sample data, check accuracy") {
      bayes::Classifier classifier(model_path, all_images);
      classifier.Classify();

      REQUIRE(classifier.GetAccuracy() > 0.60);  // limit given by instructors
      REQUIRE(classifier.GetAccuracy() <= 1);
    }
  }
}

TEST_CASE("Image and Model classes", "[model]") {
  std::ifstream images(
      "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/trainingimages");
  std::ifstream labels(
      "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/traininglabels");
  std::vector<bayes::Image> all_images =
      bayes::CreateVecOfImages(images, labels);

  SECTION("Create Model from vector of Images") {
    string modelname = "myModel";
    bayes::Model m(all_images, modelname);
    // prior for class 5
    REQUIRE(m.GetProbOfClass(5) > 0);
  }

  SECTION("Model Class edge cases") {
    string model_path =
        "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/MyModel.json";
    bayes::Model m(model_path);
    // index out of bounds
    REQUIRE(m.GetProbOfValue(28, 0, 3, 1) == -1);
    REQUIRE(m.GetProbOfValue(2, -3, 3, 1) == -1);
    // invalid value
    REQUIRE(m.GetProbOfValue(2, 3, 3, 3) == -1);
    // invalid class
    REQUIRE(m.GetProbOfValue(2, -3, 33, 1) == -1);
  }

  SECTION("Image Class") {
    // tests first 3 and last
    REQUIRE(all_images[0].GetLabel() == '5');
    REQUIRE(all_images[1].GetLabel() == '0');
    REQUIRE(all_images[2].GetLabel() == '4');
    REQUIRE(all_images[all_images.size() - 1].GetLabel() == '2');
  }

  SECTION("Image edge cases") {
    bayes::Image& i = all_images[all_images.size() - 1];

    REQUIRE(i.Get(28, 27) == '\t');
    REQUIRE(i.GetValue(28, 27) == -1);
    REQUIRE(i.Get(11, -11) == '\t');
    REQUIRE(i.GetValue(0, 28) == -1);
  }

  SECTION("Image values") {
    bayes::Image& i = all_images[0];

    // Extra print statements before and after to help see bound and because
    // clion doesn't like extra white spaces
    cout << "first image from trainingimages file" << std::endl;
    cout << "\n" << i << std::endl;
    cout << "end of image" << std::endl;

    REQUIRE(i.Get(27, 27) == ' ');
    REQUIRE(i.GetValue(27, 27) == 0);
    REQUIRE(i.Get(11, 11) == '+');
    REQUIRE(i.GetValue(11, 11) == 1);
    REQUIRE(i.Get(23, 6) == '#');
    REQUIRE(i.GetValue(23, 6) == 1);
  }
}