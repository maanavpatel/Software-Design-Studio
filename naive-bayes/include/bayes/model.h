// Copyright (c) 2020 Maanav Patel. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

#include "image.h"

namespace bayes {
// 0-9 inclusive.
constexpr size_t kNumClasses = 10;
// Shaded or not shaded.
constexpr size_t kNumShades = 2;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
class Model {
 public:
  /**
   * Makes a model using a vector of Images.
   * @param all_images a vector of Images that will be used to train the Model.
   * @param model_name a name for this model, this will also be the file name if
   * a json is made.
   */
  Model(const std::vector<Image>& all_images, const std::string& model_name);
  /**
   * Makes a model from a valid json file.
   * @param filepath path to json of a Model.
   */
  Model(const std::string& filepath);
  /**
   * Prints information about a certain class/label from the model.
   * @param label the class or label that information is wanted for.
   */
  void PrintModel(size_t label);
  /**
   * Creates a json file with a name given by the constructor or defaults to
   * 'Model.json'. The files are saved under the /data/ folder
   */
  void MakeJson();
  /**
   * Retrieve probability of class, also known as a prior.
   * @param label the class whose probability is needed.
   * @return the probability of the class.
   */
  double GetProbOfClass(size_t label);
  /**
   * Retrieve probability of given value at given coordinates.
   * @param label the class whose probability is needed.
   * @param x coordinate in x direction.
   * @param y coordinate in y direction.
   * @param val 0 for unshaded or 1 for shaded.
   * @return the probability of the class.
   */
  double GetProbOfValue(size_t label, size_t x, size_t y, size_t val);

 private:
  std::vector<Image> images;
  // The individual probabilities for each pixel for each Number for
  // whether it's shaded or not.
  double probs_[kImageSize][kImageSize][kNumClasses][kNumShades]{};
  std::map<size_t, std::vector<Image> > class_to_images;
  std::map<size_t, double> class_to_prob;
  std::string name = "Model";
  double laplace_k = 0.5;
  /**
   * Fills class_to_images map by mapping a class to a vector of Images
   */
  void MapClassToImages();
  /**
   * Calculates priors
   */
  void CalcProbOfEachClass();
  /**
   * Computes all probabilities for every pixel in an Image for all classes.
   * Sets these values within probs_[][][][]
   */
  void ComputeModelProbabilities();
  /**
   * Used to Create a Model from a json. Sets the value for all priors and all
   * values within probs_[][][][]
   * @param filepath path to json
   */
  void ParseJson(const std::string& filepath);
};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
