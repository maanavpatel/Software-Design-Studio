//
// Created by Maanav Patel on 3/31/20.
//

#include <bayes/utils.h>

namespace bayes {

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
      cout << "invalid image file" << std::endl;
      break;
    }
    ++line_count;
  }

  // have to repeat one last time once file has reached end
  // Possible improvement:use a do while loop
  string label;
  std::getline(labels, label);
  char label_char = label[0];
  Image i(image_strings, label_char);
  allImages.push_back(i);
  image_strings.clear();

  return allImages;
}
}  // namespace bayes