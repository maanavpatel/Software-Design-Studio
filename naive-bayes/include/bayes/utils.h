//
// Created by Maanav Patel on 3/31/20.
//

#ifndef NAIVEBAYES_UTILS_H
#define NAIVEBAYES_UTILS_H

#include <bayes/image.h>

#include <fstream>
#include <iostream>

using std::string;
using std::vector;

namespace bayes {
/**
 * Can create a vector of Images containing all images described in the files.
 * @param images_file file containing all images.
 * @param labels file containing labels for all the images in images_file.
 * @return a vector of all Image objects created from parsing the files.
 */
std::vector<Image> CreateVecOfImages(std::ifstream& images_file,
                                     std::ifstream& labels);

}  // namespace bayes
#endif  // NAIVEBAYES_UTILS_H
