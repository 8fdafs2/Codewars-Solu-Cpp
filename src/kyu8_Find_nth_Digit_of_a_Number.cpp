/*
https://www.codewars.com/kata/577b9960df78c19bca00007e

The function findDigit takes two numbers as input,
num and nth. It outputs the
nth digit of num (counting from right to left).

Note

    If num is negative, ignore its sign and treat it as a positive value.
    If nth is not positive, return -1.
    Keep in mind that 42 = 00042.
    This means that findDigit(42, 5) would return 0.

Examples

    findDigit(5673, 4)     returns 5
    findDigit(129, 2)      returns 2
    findDigit(-2825, 3)    returns 8
    findDigit(-456, 4)     returns 0
    findDigit(0, 20)       returns 0
    findDigit(65, 0)       returns -1
    findDigit(24, -8)      returns -1
*/

#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static int findDigit_01(int num, int nth) {
    if (nth <= 0) return -1;
    stringstream numss;
    numss << (num < 0 ? -num : num);
    string numstr = numss.str();
    if (nth > numstr.size()) return 0;
    return numstr[numstr.size() - nth] - '0';
  };

  static int findDigit_02(int num, int nth) {
    if (nth <= 0) return -1;
    num = num < 0 ? -num : num;
    int bottom = pow(10, nth - 1);
    return (num / bottom) % 10;
  };
};

int sol_(int num, int nth) {
  num = num < 0 ? -num : num;
  if (nth <= 0) return -1;
  return ((num % (int)pow(10, nth)) - (num % (int)pow(10, (nth - 1)))) /
         (int)pow(10, (nth - 1));
}

void test(int (*findDigit)(int, int)) {
  // random test
  for (int i = 0; i < 10; i++) {
    int rand_num = rand() % 100000 - 50000;
    int rand_nth = rand() % 11 - 2;
    assert(findDigit(rand_num, rand_nth) == sol_(rand_num, rand_nth));
  }
}

int main() {
  Solution sol;
  test(sol.findDigit_01);
  test(sol.findDigit_02);
  return 0;
}