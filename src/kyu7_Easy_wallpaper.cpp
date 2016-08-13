/*
https://www.codewars.com/kata/easy-wallpaper

John wants to decorate a room with wallpaper. He has been said that making sure
he has the right amount of wallpaper is more complex than it sounds. He wants a
fool-proof method to getting it right.

John knows that the rectangular room has a length of l meters, a width of w
meters, a height of h meters. The standard width of the rolls he wants to buy is
52 centimeters. The length of a roll is 10 meters. He bears in mind however,
that it’s best to have an extra length of wallpaper handy in case of mistakes or
miscalculations so he wants to buy a length 15% greater than the one he needs.

Last time he did these calculations he caught a headache so could you help John?
Your function wallpaper(l, w, h) should return as a plain English word in lower
case the number of rolls he must buy.

Example:

wallpaper(4, 3.5, 3) should return "ten"

Notes:

all rolls (even with incomplete width) are put edge to edge
0 <= l, w, h (floating numbers), it can happens that w x h x l is zero
the integer r (number of rolls) will always be less or equal to 20
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static string wallPaper_01(double l, double w, double h) {
    const map<int, string> mapi2s = {
        {0, "zero"},     {1, "one"},        {2, "two"},       {3, "three"},
        {4, "four"},     {5, "five"},       {6, "six"},       {7, "seven"},
        {8, "eight"},    {9, "nine"},       {10, "ten"},      {11, "eleven"},
        {12, "twelve"},  {13, "thirteen"},  {14, "fourteen"}, {15, "fifteen"},
        {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"},
        {20, "twenty"},
    };
    const double a_roll = 0.52 * 10;
    double a = (l + w) * 2 * h * 1.15;
    int n = ceil(a / a_roll);
    auto it = mapi2s.find(n);
    if (it != mapi2s.end()) return it->second;
  };

  static string wallPaper_02(double l, double w, double h) {
    int rolls =
        ceil((l + w) * 0.4423 * h);  // (2 * 1.15) / (0.25 * 10) = 0.4423....
    const string n[] = {"zero", "one",    "two",    "three",   "four",
                        "five", "six",    "seven",  "eight",   "nine",
                        "ten",  "eleven", "twelve", "thirteen"};
    return rolls == 20
               ? "twenty"
               : rolls == 18
                     ? "eighteen"
                     : rolls == 15
                           ? "fifteen"
                           : rolls <= 13 ? n[rolls] : n[rolls - 10] + "teen";
  };

  static string wallPaper_03(double l, double w, double h) {
    const vector<string> numbersTests = {
        "zero",     "one",      "two",      "three",   "four",    "five",
        "six",      "seven",    "eight",    "nine",    "ten",     "eleven",
        "twelve",   "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
        "eighteen", "nineteen", "twenty"};
    if ((l + w) == 0 || h == 0) {
      return numbersTests[0];
    }
    return numbersTests[static_cast<int>(
        ceil((((l + w) * 2 * h) / 5.2) * 1.15))];
  };
};

class TestCase {
 public:
  double l;
  double w;
  double h;
  string expected;
  TestCase(int l_, int w_, int h_, const string &expected_)
      : l(l_), w(w_), h(h_), expected(expected_) {
    // Constructor
  }
};

random_device rd;
mt19937 rng(rd());

const vector<TestCase> set_gen(
    const function<string(int, int, int)> &wallPaper) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(1, 90);
  uniform_int_distribution<int> uni2(1, 70);
  uniform_int_distribution<int> uni3(220, 335);
  for (int i = 0; i < 100; i++) {
    double l = uni1(rng) / 10.0;
    double w = uni2(rng) / 10.0;
    double h = uni3(rng) / 100.0;
    int r = static_cast<int>(ceil((((l + w) * 2 * h) / 5.2) * 1.15));
    if (r < 21) {
      string expected = wallPaper(l, w, h);
      testcases.push_back(TestCase(l, w, h, expected));
    }
  }
  return testcases;
}

void test(const function<string(int, int, int)> &wallPaper,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(wallPaper(testcase.l, testcase.w, testcase.h) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(int, int, int)> &wallPaper,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) wallPaper(testcase.l, testcase.w, testcase.h);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.wallPaper_01);
  test(sol.wallPaper_01, testcases);
  test(sol.wallPaper_02, testcases);
  test(sol.wallPaper_03, testcases);
  cout << "wallPaper_01:\t" << test_spd(sol.wallPaper_01, testcases) << "ms"
       << endl;
  cout << "wallPaper_02:\t" << test_spd(sol.wallPaper_02, testcases) << "ms"
       << endl;
  cout << "wallPaper_03:\t" << test_spd(sol.wallPaper_03, testcases) << "ms"
       << endl;
  return 0;
}