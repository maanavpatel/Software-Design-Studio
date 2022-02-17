//
// Created by Maanav Patel on 3/19/20.
//

#include <sudoku/file-helper.h>

namespace sudoku {
void FileHelper::SetFilePath(string& file_path_to_spf) {
  file_path = file_path_to_spf;
}

bool FileHelper::IsVersionCompatible() {
  string version_line;
  getline(this->GetIstream(), version_line);
  if (version_line.compare(kfileTag) == 0) {
    cout << "filepath is valid and tag is correct" << endl;
    return true;
  }
  cout << "incompatible file type" << endl;
  return false;
}

ifstream FileHelper::GetIstream() {
  ifstream file_stream(file_path);
  return file_stream;
}

bool FileHelper::IsPuzzleValid(const string& puzzle) {
  if (puzzle.length() == size * size) {
    char maxSizeChar = (char)('0' + size);
    for (char value : puzzle) {
      /* all values in a puzzle must be between 1 and the size of the game or
       * an underscore for empty spaces
       * recall the traditional size for sudoku is 9
       */
      if ((value < '1' || value > maxSizeChar) && value != '_') {
        return false;
      }
    }
    return true;
  }
  return false;
}
}  // namespace sudoku
