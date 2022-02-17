// Copyright 2020 Maanav Patel. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>

#include <nlohmann/json.hpp>

namespace bayes {

Classifier::Classifier(std::string& model_filepath,
                       std::vector<Image>& all_images) {
  filepath = model_filepath;
  images = all_images;
}

void Classifier::Classify() {
  Model model(filepath);
  // look through all images
  for (size_t i = 0; i < images.size(); ++i) {
    size_t classifcation = ClassifyImage(model, images[i]);
    image_to_classification[i] = classifcation;
  }
}

size_t Classifier::ClassifyImage(Model& model, Image& image) {
  // look through pixels and calculate maximum a posteriori (MAP) classification
  std::map<size_t, double> label_to_MAP_val;
  for (size_t i = 0; i < kNumClasses; ++i) {
    // i is the class
    double class_prior = model.GetProbOfClass(i);
    double sum_log_prob = 0;
    for (size_t j = 0; j < kImageSize; ++j) {    // j is x coordinate
      for (size_t k = 0; k < kImageSize; ++k) {  // k is y coordinate
        size_t value = image.GetValue(j, k);
        double prob = model.GetProbOfValue(i, j, k, value);  // raw prob
        double log_prob = log(prob);  // log to avoid very small values
        sum_log_prob += log_prob;
      }
    }
    double map_value = class_prior + sum_log_prob;
    label_to_MAP_val[i] = map_value;
  }
  return FindMostLikely(label_to_MAP_val);
}

size_t Classifier::FindMostLikely(std::map<size_t, double>& label_to_MAP_val) {
  double max_val = label_to_MAP_val[0];  // set the max to the first value
  size_t max_label = 0;
  for (size_t i = 0; i < label_to_MAP_val.size(); ++i) {
    double map_val = label_to_MAP_val[i];
    if (max_val < map_val) {
      max_val = map_val;
      max_label = i;
    }
  }
  return max_label;
}

double Classifier::GetAccuracy() {
  size_t correct_classification_count = 0;
  for (size_t i = 0; i < images.size(); i++) {
    char label = images[i].GetLabel();
    size_t converted_label = label - '0';
    if (image_to_classification[i] == converted_label) {
      ++correct_classification_count;
    }
  }
  double accuracy = ((double)correct_classification_count) / images.size();
  return accuracy;
}
void Classifier::PrintClassifications() {
  cout << "classification <- truth" << std::endl;
  for (size_t i = 0; i < image_to_classification.size(); ++i) {
    cout << image_to_classification[i] << " <- " << (char)images[i].GetLabel();
    cout << std::endl;
  }
}

}  // namespace bayes
