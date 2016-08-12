/*
https://www.codewars.com/kata/55685cd7ad70877c23000102

In this simple assignment you are given a number and have to make it negative.
But maybe the number is already negative?

Example:

    makeNegative(1); // return -1
    makeNegative(-5); // return -5
    makeNegative(0); // return 0

Notes:

    The number can be negative already, in which case no change is required.
    Zero (0) can't be negative, see examples above.
*/

#include <cassert>
#include <ctime>
#include <iostream>

class Solution {
 public:
  static int makeNegative_01(int num) {
    if (num > 0) {
      return -num;
    }
    return num;
  }
  static int makeNegative_02(int num) { return num > 0 ? -num : num; }
};

void test(int (*makeNegative)(int)) {
  srand(time(0));
  // should_handle_positive_test
  assert(makeNegative(42) == -42);
  // should_handle_negative_test
  assert(makeNegative(-9) == -9);
  // should_handle_zero_test
  assert(makeNegative(0) == 0);
  // should_handle_random_positive_test
  int rnd = rand() % 100;
  assert(makeNegative(rnd) == -rnd);
  // should_handle_random_negative_test
  rnd = -(rand() % 100);
  assert(makeNegative(rnd) == rnd);
  // std::cout << rnd << std::endl;
}

int main() {
  Solution sol;
  test(sol.makeNegative_01);
  test(sol.makeNegative_02);
  return 0;
}