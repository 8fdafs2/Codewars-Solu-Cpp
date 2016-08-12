/*
https://www.codewars.com/kata/thinking-and-testing-a-and-b

No Story

No Description

Only by Thinking and Testing

Look at result of testcase, guess the code!
*/

#include <cassert>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static int testit_01(int a, int b) { return a | b; };
};

bit_or<int> sol_;

void test(int (*testit)(int, int)) {
  // random test
  for (int i = 0; i < 100; i++) {
    int randomA = rand() % 1000 + 1;
    int randomB = rand() % 1000 + 1;
    int expected = sol_(randomA, randomB);
    assert(expected == testit(randomA, randomB));
  }
}

int main() {
  Solution sol;
  test(sol.testit_01);
  return 0;
}