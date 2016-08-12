/*
https://www.codewars.com/kata/a-function-within-a-function

Given an input n, write a function always that returns a function which returns
n. Ruby should return a lambda or a proc.

function<int (void)> three = always(3);
three(); // returns 3
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static function<int(void)> always_01(int x) {
    function<int(void)> f = [x]() { return x; };
    return f;
  }
  static function<int(void)> always_02(int x) {
    return [=]() { return x; };
  }
};

void test(function<int(void)> (*always)(int)) {
  // random
  for (int i = 0; i < 10; i++) {
    int random_n = rand() % 20;
    function<int(void)> fp = always(random_n);
    assert(fp() == random_n);
  }
}

int main() {
  Solution sol;
  test(sol.always_01);
  test(sol.always_02);
  return 0;
}