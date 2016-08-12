/*
https://www.codewars.com/kata/53369039d7ab3ac506000467

Complete the bool_to_word (Javascript: boolToWord ) method.
Given: a boolean value
Return: a 'Yes' string for true and a 'No' string for false
*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  static string bool_to_word_01(bool value) {
    return value ? "Yes" : "No";
  };
};

void test(string (*bool_to_word)(bool)) {
  // ...
  assert(bool_to_word(true) == "Yes");
  assert(bool_to_word(false) == "No");
}

int main() {
  Solution sol;
  test(sol.bool_to_word_01);
  return 0;
}