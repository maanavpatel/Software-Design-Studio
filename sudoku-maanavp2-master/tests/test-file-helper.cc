//
// Created by Maanav Patel on 3/22/20.
//
#include <sudoku/file-helper.h>

#include <catch2/catch.hpp>
namespace sudoku {
TEST_CASE("only version tag #spf1.0 should work", "[version]") {
  FileHelper file_helper;
  string file_path;
  SECTION("valid version") {
    file_path = "data/example.spf";
    file_helper.SetFilePath(file_path);
    REQUIRE(file_helper.IsVersionCompatible());
  }

  SECTION("invalid version") {
    file_path = "data/badversion.spf";
    // first line of this file is: #spf1.4 which does not match #spf1.0
    file_helper.SetFilePath(file_path);
    REQUIRE(!file_helper.IsVersionCompatible());
  }
}

TEST_CASE("81 length and legal characters are valid format for puzzles",
          "[valid-format]") {
  /*
   * the length of the given puzzle string should be 81 and all values should
   * be numbers between 1 and 9 or an underscore.
   */
  FileHelper file_helper;
  SECTION("valid formats") {
    string puzzle;
    // simple valid format (from example.spf)
    puzzle =
        "85___24__72______9__4_________1_7__"
        "23_5___9___4___________8__7__17__________36_4_";
    REQUIRE(file_helper.IsPuzzleValid(puzzle));
    // other simple (from example.spf)
    puzzle =
        "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____"
        "248___9____5______6___";
    REQUIRE(file_helper.IsPuzzleValid(puzzle));

    // although this puzzle is unsolvable/impossible it is in the correct format
    puzzle =
        "85111241172111111911411455677111711"
        "2315111911141112222221181171117111111111136141";
    REQUIRE(file_helper.IsPuzzleValid(puzzle));
  }

  SECTION("invalid formats") {
    string puzzle;
    // empty string
    puzzle = "";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));

    // 81 length but 0 cannot be a number
    puzzle =
        "85_0_24__72______9__4_________1_7__"
        "23_5___9___4___________8__7__17__________36_4_";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));

    // 81 length but / cannot be a value
    puzzle =
        "_3_1_76__72____8_9__4____/____1_7__"
        "23_5___9___4____/______8__7__17__________36_4_";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));

    // under 81 length
    puzzle = "2315111911141112222221181171117111111111136141";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));

    // over 81 length
    puzzle =
        "85_0_24__72____8__7__17________9__4_________1_7__"
        "23_5___9___4_____0_24__72____8__7__17___0_24__72____8__7__17______";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));

    // under 81 length and invalid characters
    puzzle = "___12__4_abcdefg__5_3__9";
    REQUIRE(!file_helper.IsPuzzleValid(puzzle));
  }
}
}  // namespace sudoku
