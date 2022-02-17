// Copyright 2020 Maanav Patel. All rights reserved.

#include <bayes/model.h>

#include <nlohmann/json.hpp>

namespace bayes {

Model::Model(const std::vector<Image>& all_images,
             const std::string& model_name) {
  images = all_images;
  name = model_name;
  MapClassToImages();
  CalcProbOfEachClass();
  ComputeModelProbabilities();
  MakeJson();
}

Model::Model(const std::string& filepath) { ParseJson(filepath); }

void Model::MapClassToImages() {
  for (Image& i : images) {
    // changes from a char between '0'-'9' to an int between 0-9;
    size_t label = i.GetLabel() - '0';
    class_to_images[label].push_back(i);
  }
}

void Model::CalcProbOfEachClass() {
  for (size_t i = 0; i < kNumClasses; ++i) {
    size_t count_of_class = class_to_images[i].size();
    size_t totalSum = 0;
    for (size_t j = 0; j < kNumClasses; ++j) {
      totalSum += class_to_images[j].size();
    }
    double prob = ((double)(count_of_class)) / totalSum;
    class_to_prob[i] = prob;
  }
}

void Model::MakeJson() {
  nlohmann::json js;                          // json
  for (size_t i = 0; i < kNumClasses; ++i) {  // iterate through all classes
    js[i]["prior"] = class_to_prob[i];        // set the prior
    js[i]["probabilities"] = {};  // probabilities will be a 2d array
    for (size_t j = 0; j < kImageSize; ++j) {
      for (size_t k = 0; k < kImageSize; ++k) {
        // set the prob of a shaded pixel for the class
        js[i]["probabilities"][j][k] = probs_[j][k][i][1];
      }
    }
  }
  // out put to file
  std::ofstream outputFile(
      "/Users/maanav18/CLionProjects/naive-bayes-maanavp2/data/" + name +
      ".json");
  // outputs the json in a readable format
  outputFile << js.dump(3);
  outputFile.close();
}

void Model::PrintModel(const size_t label) {
  if (label >= 0 && label < kNumClasses) {
    std::cout << "Prior:" << std::endl;
    std::cout << label << "\t" << class_to_prob[label] << std::endl;
    std::cout << "Probabilities:" << std::endl;
    for (size_t i = 0; i < kImageSize; ++i) {
      for (size_t j = 0; j < kImageSize; ++j) {
        std::cout << "(" << i << "," << j << ")" << probs_[i][j][label][1]
                  << "\t";
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "Label out of bounds" << std::endl;
  }
}

void Model::ComputeModelProbabilities() {
  // the key: is for the coordinates of a pixel,
  // the value: will be the count of shaded pixels for the class
  for (size_t i = 0; i < class_to_images.size(); ++i) {
    std::map<std::pair<size_t, size_t>, size_t> pixel_to_shaded_count;
    // look through each image in all classes
    for (Image image : class_to_images[i]) {
      // look through each pixel
      for (size_t j = 0; j < kImageSize; ++j) {
        for (size_t k = 0; k < kImageSize; ++k) {
          // shaded values will be 1
          if (image.GetValue(j, k) == 1) {
            std::pair<size_t, size_t> coor(j, k);
            // increase the count of shaded pixels at position j,k
            ++pixel_to_shaded_count[coor];
          }
        }
      }
    }
    // look through the map pixels_to_shaded_count to calculate the prob
    for (size_t j = 0; j < kImageSize; ++j) {
      for (size_t k = 0; k < kImageSize; ++k) {
        // shaded values will be 1
        std::pair<size_t, size_t> coor(j, k);
        double numerator = laplace_k + pixel_to_shaded_count[coor];
        // the count of images that have a given label/class
        double count_images = class_to_images[i].size();
        double denominator = (2 * laplace_k) + count_images;
        double prob_of_shaded = numerator / denominator;
        probs_[j][k][i][1] = prob_of_shaded;
        probs_[j][k][i][0] = 1 - prob_of_shaded;
      }
    }
  }
}

void Model::ParseJson(const std::string& filepath) {
  std::ifstream jsonFile(filepath);
  if (jsonFile) {
    nlohmann::json js;
    jsonFile >> js;
    for (size_t i = 0; i < kNumClasses; ++i) {
      class_to_prob[i] = js[i]["prior"];
      for (size_t j = 0; j < kImageSize; ++j) {
        for (size_t k = 0; k < kImageSize; ++k) {
          double prob = js[i]["probabilities"][j][k];
          probs_[j][k][i][1] = prob;
          probs_[j][k][i][0] = 1 - prob;
        }
      }
    }
  }
}

double Model::GetProbOfValue(size_t label, size_t x, size_t y, size_t val) {
  if (label >= 0 && label < kNumClasses && x >= 0 && y >= 0 && x < kImageSize &&
      y < kImageSize && (val == 0 || val == 1)) {
    return probs_[x][y][label][val];
  } else {
    //    cout << label << ' ' << x << y << " val: " << val << std::endl;
    return -1;
  }
}

double Model::GetProbOfClass(size_t label) {
  if (label >= 0 && label < kNumClasses) {
    return class_to_prob[label];
  }
  return -1;
}

}  // namespace bayes
