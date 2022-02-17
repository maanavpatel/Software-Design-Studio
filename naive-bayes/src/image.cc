// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>

namespace bayes {

char Image::Get(size_t x, size_t y) {
  if (x >= 0 && x < kImageSize && y >= 0 && y < kImageSize) {
    return pixels[x][y];
  }
  return '\t';
}

char Image::GetLabel() { return label; }

Image::Image(std::vector<std::string>& lines, char true_label) {
  label = true_label;
  for (size_t i = 0; i < lines.size(); ++i) {
    std::vector<char> line;
    for (size_t j = 0; j < kImageSize; ++j) {
      char c = lines[i][j];
      line.push_back(c);
    }
    pixels.push_back(line);
  }
}

std::ostream& operator<<(std::ostream& os, Image& image) {
  for (size_t i = 0; i < kImageSize; ++i) {
    for (size_t j = 0; j < kImageSize; ++j) {
      os << image.pixels[i][j];
    }
    os << std::endl;
  }
  return os;
}
int Image::GetValue(size_t x, size_t y) {
  if (!pixels.empty() && x >= 0 && x < kImageSize && y >= 0 && y < kImageSize) {
    char pixel = pixels[x][y];
    if (pixel == ' ') {
      return 0;
    } else {
      return 1;
    }
  }
  return -1;
}
}  // namespace bayes
