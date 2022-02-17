// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <iostream>
#include <vector>
using std::cout;

namespace bayes {
constexpr size_t kImageSize = 28;

class Image {
 public:
  Image(std::vector<std::string>& lines, char true_label);
  /**
   * Get the character in the Image at given pixel position.
   * @param x coordinate of pixel in x direction.
   * @param y coordinate of pixel in y direction.
   * @return character at given position or a tab character
   * if the coordinates are out of bounds.
   */
  char Get(size_t x, size_t y);
  /**
   * Get the value of a pixel within an Image.
   * @param x coordinate of pixel in x direction.
   * @param y coordinate of pixel in y direction.
   * @return value at given position or -1 if the coordinates are out of bounds.
   */
  int GetValue(size_t x, size_t y);
  /**
   * Gets the label (true classification) of the Image.
   * @return character that is the label for the Image.
   */
  char GetLabel();
  /**
   * Outputs the Image in a readable format
   * @param os out-stream to output to.
   * @param image Image to be outputted.
   * @return modified out-stream.
   */
  friend std::ostream& operator<<(std::ostream& os, Image& image);

 private:
  /**
   * True label/classification of Image.
   */
  char label;
  /**
   * 2d vector to hold all pixels.
   */
  std::vector<std::vector<char> > pixels;
};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
