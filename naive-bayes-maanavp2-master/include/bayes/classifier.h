// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include "model.h"

namespace bayes {
class Classifier {
 public:
  /**
   * Creates a Classifier from a given model filepath and vector of Images.
   * @param model_filepath file path to model that will be used to classify.
   * @param all_images all images that want to be classified.
   */
  Classifier(std::string& model_filepath, std::vector<Image>& all_images);
  /**
   * Assigns Classifications for all Images.
   */
  void Classify();
  /**
   * Returns the accuracy of the model/classifier.
   * @return double representing probability that the classifier will correctly
   * classify an Image.
   */
  double GetAccuracy();
  /**
   * Prints out all classifications and the value they actually should be.
   * classification <- truth
   * @return
   */
  void PrintClassifications();

 private:
  std::vector<Image> images;  // all Images to be classified
  /**
   * Map to the classification of each image, the first size_t value is an index
   * for the image in the vector images, the second is the given classification.
   */
  std::map<size_t, size_t> image_to_classification;
  std::string filepath;  // file path to model
  /**
   * Classifies an image using a given model.
   * @param model a reference to a Model.
   * @param image a reference to an Image that is to be classified.
   * @return size_t representing the classification.
   */
  size_t ClassifyImage(Model& model, Image& image);
  /**
   * Looks through a map from labels to posteriori values
   * @param label_to_MAP_val
   * @return
   */
  size_t FindMostLikely(std::map<size_t, double>& label_to_MAP_val);
};
}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_
