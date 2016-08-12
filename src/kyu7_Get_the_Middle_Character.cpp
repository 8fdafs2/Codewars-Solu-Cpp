/*
https://www.codewars.com/kata/get-the-middle-character

You are going to be given a word. Your job is to return the middle character of
the word. If the word"s length is odd, return the middle character. If the
word"s length is even, return the middle 2 characters.

Examples:

  Kata.getMiddle("test") should return "es"
  Kata.getMiddle("testing") should return "t"
  Kata.getMiddle("middle") should return "dd"
  Kata.getMiddle("A") should return "A"

Input

  A word (string) of length 0 < str < 1000

Output

  The middle character(s) of the word represented as a string.
*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>

class Solution {
 public:
  static std::string get_middle_01(std::string input) {
    int len = input.length();
    if (len % 2 == 0) {
      return input.substr(len / 2 - 1, 2);
    } else {
      return input.substr((len - 1) / 2, 1);
    }
  };
  static std::string get_middle_02(std::string input) {
    return input.substr(input.length() / 2 - 1 + input.length() % 2,
                        (input.length() % 2) ? 1 : 2);
  };
  static std::string get_middle_03(std::string input) {
    return std::string(1, input[floor((input.size() - 1) / 2)]) +
           ((input.size() % 2) ? "" : std::string(1, input[input.size() / 2]));
  };
};

std::string get_middle_(std::string input) {
  int half = input.length() / 2;
  if (input.length() % 2 == 0) {
    return input.substr(half - 1, 2);
  } else {
    return input.substr(half, 1);
  }
}

std::string generate_random() {
  int length = rand() % 100 + 1;
  std::string random;
  for (int i = 0; i < length; i++) {
    int asciiVal = rand() % 26 + 97;
    random += static_cast<char>(asciiVal);
  }
  return random;
}

void test(std::string (*get_middle)(std::string)) {
  // should_handle_basic_tests
  assert(get_middle("test") == "es");
  assert(get_middle("testing") == "t");
  assert(get_middle("middle") == "dd");
  assert(get_middle("A") == "A");
  // should_handle_stranger_cases
  assert(get_middle("aaaaaaaaaaaeeeeeeeeeeeeyyyyyyyyyyyyyuu") == "ee");
  assert(get_middle("aaaaaaaaaaafffeeeeeeeeeeeeg") == "f");
  assert(get_middle("45321096") == "21");
  assert(get_middle("NiceToMeetYou") == "M");
  // should_handle_random_test_cases
  for (int i = 0; i < 10; i++) {
    std::string random = generate_random();
    assert(get_middle(random) == get_middle_(random));
  }
}

int main() {
  Solution sol;
  test(sol.get_middle_01);
  test(sol.get_middle_02);
  test(sol.get_middle_03);
  return 0;
}