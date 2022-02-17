// Copyright (c) 2020 Maanav Patel. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cs126linkedlist/ll.h>

#include <catch2/catch.hpp>

using cs126linkedlist::LinkedList;
using std::cout, std::endl;
// Read more on SECTIONs here:
// `https://github.com/catchorg/Catch2/tree/master/docs`
// in the "Test Cases and Sections" file.

TEST_CASE("Push Back", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push back one element") {
    list.push_back(1);
    REQUIRE(list.size() == 1);
  }

  SECTION("Push back two elements") {
    list.push_back(-1);
    list.push_back(10000);
    REQUIRE(list.size() == 2);
  }
}

TEST_CASE("Push Front", "[constructor][push_front][front][back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push front one element") {
    list.push_front(1);
    REQUIRE(list.size() == 1);
  }

  SECTION("Push front six elements") {
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);
    list.push_front(6);
    list.push_front(7);
    list.push_front(8);
    cout << list << endl;
    REQUIRE(list.size() == 6);
    SECTION("Check front and back elements") {
      REQUIRE(list.front() == 8);
      REQUIRE(list.back() == 3);
    }
  }
}

TEST_CASE("Pop Front",
          "[pop_front][push_front][push_back][front][back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Pop front empty list") {
    list.pop_front();
    REQUIRE(list.empty());
  }

  SECTION("Pop front one element") {
    list.push_front(1);
    list.pop_front();
    REQUIRE(list.empty());
  }

  SECTION("Push three then Pop front one element") {
    list.push_front(1);
    list.push_front(5);
    list.push_back(9);
    list.pop_front();
    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 9);
  }
}

TEST_CASE("Pop back", "[pop_back][push_front][push_back][size][empty][back]") {
  LinkedList<int> list;

  SECTION("Pop back empty list") {
    list.pop_back();
    REQUIRE(list.empty());
  }

  SECTION("Pop back one element") {
    list.push_front(1);
    list.pop_back();
    REQUIRE(list.empty());
  }

  SECTION("Push three then Pop back one element") {
    list.push_front(3);
    list.push_front(2);
    list.push_back(6);
    // 2 -> 3 -> 6
    list.pop_back();
    REQUIRE(list.size() == 2);
    REQUIRE(list.back() == 3);
  }
}

TEST_CASE("Remove nth", "[remove_nth][push_front][push_back][size][empty]") {
  LinkedList<int> list;

  SECTION("Remove from empty list") {
    list.RemoveNth(3);
    // should do nothing
    REQUIRE(list.empty());
  }

  SECTION("Remove first element from size 1") {
    list.push_back(5);
    list.RemoveNth(0);
    REQUIRE(list.empty());
  }

  SECTION("Remove elements from size 8") {
    // add elements to list
    list.push_back(12);
    list.push_back(22);
    list.push_back(123);
    list.push_back(214);
    list.push_back(50);
    list.push_back(56);
    list.push_back(95);
    list.push_back(5);

    list.RemoveNth(3);
    list.RemoveNth(20);  // no effect
    REQUIRE(list.size() == 7);
    list.RemoveNth(7);  // no effect
    list.RemoveNth(2);
    list.RemoveNth(4);
    REQUIRE(list.size() == 5);
  }
}

TEST_CASE("Remove odd", "[remove_odd][push_back][front][back][size][empty]") {
  LinkedList<int> list;

  SECTION("Remove from empty list") {
    list.RemoveOdd();
    // should do nothing
    REQUIRE(list.empty());
  }

  SECTION("Remove from list of size 1") {
    list.push_back(4);
    list.RemoveOdd();
    // should do nothing
    REQUIRE(list.size() == 1);
    list.pop_back();
    REQUIRE(list.empty());
  }

  SECTION("Remove from list of size 5") {
    list.push_back(12);
    list.push_back(22);
    list.push_back(123);
    list.push_back(214);
    list.push_back(50);
    list.RemoveOdd();
    REQUIRE(list.size() == 3);
    list.pop_back();  // remove 50
    REQUIRE(list.back() == 123);
  }
}

TEST_CASE("Clear", "[push_back][clear][back][size][empty]") {
  LinkedList<int> list;

  SECTION("Clear from empty list") {
    list.clear();
    // should do nothing
    REQUIRE(list.empty());
  }

  SECTION("clear list of size 5") {
    list.push_back(12);
    list.push_back(22);
    list.push_back(123);
    list.push_back(214);
    list.push_back(50);
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }

  SECTION("add/remove elements, clear repeat") {
    list.push_back(4);
    list.push_back(2);
    list.push_back(3);
    list.clear();
    list.push_back(3);
    list.push_back(98);
    list.pop_back();
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }
}

TEST_CASE("!= and == operator", "[not_eq][eq][push_back]") {
  LinkedList<int> list;
  LinkedList<int> other_list;

  SECTION("both empty") {
    REQUIRE(list == other_list);
    REQUIRE(!(list != other_list));
  }

  SECTION("one empty list, one not") {
    other_list.push_back(3);
    REQUIRE(list != other_list);
    REQUIRE(!(list == other_list));
  }

  SECTION("reverse lists") {
    list.push_back(12);
    list.push_back(22);
    list.push_back(123);
    list.push_back(214);
    list.push_back(50);
    cout << list << endl;
    other_list.push_back(50);
    other_list.push_back(214);
    other_list.push_back(123);
    other_list.push_back(22);
    other_list.push_back(12);
    cout << other_list << endl;
    REQUIRE(list != other_list);
    REQUIRE(!(list == other_list));
  }

  SECTION("different sizes") {
    list.push_back(4);
    list.push_back(2);
    list.push_back(3);

    other_list.push_back(3);
    other_list.push_back(98);

    REQUIRE(list != other_list);
    REQUIRE(!(list == other_list));
  }

  SECTION("same list") {
    list.push_back(4);
    list.push_back(2);
    list.push_back(3);
    REQUIRE(list == list);
    REQUIRE(!(list != list));
  }

  SECTION("equal lists") {
    list.push_back(4);
    list.push_back(2);
    list.push_back(3);

    other_list.push_back(4);
    other_list.push_back(2);
    other_list.push_back(3);
    REQUIRE(list == other_list);
    REQUIRE(!(list != other_list));
  }

  SECTION("almost equal lists") {
    list.push_back(4);
    list.push_back(2);
    list.push_back(3);
    list.push_back(-3);

    other_list.push_back(4);
    other_list.push_back(2);
    other_list.push_back(3);
    other_list.push_back(3);
    REQUIRE(list != other_list);
    REQUIRE(!(list == other_list));
  }
}

TEST_CASE("Constructors", "[constructors][empty][push_back][size]") {
  SECTION("Copy Constructor") {
    LinkedList<int> list;

    SECTION("empty lists") {
      LinkedList<int> other_list(list);
      REQUIRE(list == other_list);
    }

    SECTION("small sample list") {
      list.push_back(3);
      list.push_back(6);
      list.push_back(9);
      list.push_back(12);

      LinkedList<int> other_list(list);
      cout << "small sample list: " << other_list << endl;
      REQUIRE(list == other_list);
    }

    SECTION("should be independent") {
      list.push_back(3);
      list.push_back(6);

      LinkedList<int> other_list(list);
      other_list.push_back(0);
      list.push_back(9);
      cout << "small sample list: " << other_list << endl;
      REQUIRE(list != other_list);
      REQUIRE(list.back() == 9);
      REQUIRE(other_list.back() == 0);
    }
  }

  SECTION("Vector Constructor") {
    SECTION("Empty Vector") {
      std::vector<int> v = {};
      LinkedList<int> list(v);
      REQUIRE(list.empty());
    }

    SECTION("Non empty") {
      std::vector<int> v = {11, 12, 3, 4, 4, 4, 5};
      size_t size = v.size();
      LinkedList<int> list(v);
      cout << "from vector: " << list << endl;
      REQUIRE(size == list.size());
      REQUIRE(11 == list.front());
      v.pop_back();  // changing the vector shouldn't change the list
      REQUIRE(5 == list.back());
    }
  }

  SECTION("Move Constructor") {
    SECTION("Empty list") {
      LinkedList<int> list;
      LinkedList<int> move_to(std::move(list));
      REQUIRE(list.empty());
      REQUIRE(move_to.empty());
    }

    SECTION("Non empty") {
      std::vector<int> v = {1, 3, 4, 5, 8};
      size_t size = v.size();
      LinkedList<int> list(v);
      LinkedList<int> dest(std::move(list));
      REQUIRE(list.empty());
      REQUIRE(dest.front() == 1);
      dest.pop_back();
      REQUIRE(dest.back() == 5);
    }
  }
}

TEST_CASE("Assignment Operators", "[assignment_ops][empty][push_back][size]") {
  LinkedList<int> list;
  SECTION("Copy assignment") {
    SECTION("empty") { LinkedList<int> other = list; }

    SECTION("list non-empty") {
      list.push_back(7);
      list.push_back(8);
      list.push_back(9);

      LinkedList<int> other = list;

      REQUIRE(!other.empty());
      REQUIRE(other.front() == list.front());

      list.pop_front();
      REQUIRE(list.front() != other.front());
      other.pop_back();
      other.push_back(3);

      REQUIRE(list != other);
    }

    SECTION("both non-empty") {
      list.push_back(7);
      list.push_back(8);
      list.push_back(9);

      LinkedList<int> other;
      other.push_back(3);
      other.push_back(2);
      other.push_back(1);

      other = list;
      REQUIRE(other.back() == 9);
      REQUIRE(!other.empty());
      REQUIRE(other.front() == list.front());

      list.pop_front();
      REQUIRE(list.front() != other.front());
      other.pop_back();
      other.push_back(3);
      REQUIRE(list != other);
    }
  }

  SECTION("Move Assignment") {
    SECTION("Empty list") {
      LinkedList<int> list;
      LinkedList<int> move_to = std::move(list);
      REQUIRE(list.empty());
      REQUIRE(move_to.empty());
    }

    SECTION("Non empty") {
      std::vector<int> v = {1, 3, 4, 5, 8};
      size_t size = v.size();
      LinkedList<int> list(v);
      LinkedList<int> dest = std::move(list);
      REQUIRE(list.empty());
      REQUIRE(dest.front() == 1);
      dest.pop_back();
      REQUIRE(dest.back() == 5);
    }
  }
}

TEST_CASE("Iterators") {
  SECTION("iterator") {
    LinkedList<int> list;

    SECTION("empty list") {
      auto iter = list.begin();
      REQUIRE(!(list.end() != iter));
    }

    SECTION("single item list") {
      list.push_back(9);
      auto iter = list.begin();
      REQUIRE(*iter == 9);
    }

    SECTION("multi item list") {
      list.push_back(67);
      list.push_back(87);
      list.push_back(97);
      auto iter = list.begin();
      REQUIRE(*iter == 67);
      *iter = 8;
      REQUIRE(*iter == 8);
      ++iter;
      REQUIRE(*iter == 87);
      ++iter;
      *iter = 0;
      REQUIRE(*iter == 0);
      ++iter;
      REQUIRE(!(iter != list.end()));
    }
  }

  SECTION("const iterator") {
    SECTION("empty list") {
      const LinkedList<int> list;
      auto iter = list.begin();
      REQUIRE(!(list.end() != iter));
    }

    SECTION("multi item list") {
      const std::vector<int> v = {67, 87, 97};
      const LinkedList<int> list(v);
      auto iter = list.begin();
      REQUIRE(*iter == 67);
      ++iter;
      REQUIRE(*iter == 87);
      ++iter;
      REQUIRE(*iter == 97);
      ++iter;
      REQUIRE(!(iter != list.end()));
    }
  }
}