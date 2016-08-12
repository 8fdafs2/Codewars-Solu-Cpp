/*
https://www.codewars.com/kata/tortoise-racing

Two tortoises named A and B must run a race. A starts with an average speed of
720 feet per hour. Young B knows she runs faster than A and furthermore has not
finished her cabbage.

When she starts, at last, she can see that A has a 70 feet lead but B speed is
850 feet per hour. How long will it take B to catch A?

More generally: given two speeds v1 (A speed, integer > 0) and v2 (B speed,
integer > 0) and a lead g (integer > 0) how long will it take B to catch A?

The result will be an array [h, mn, s] where h, mn, s is the time needed in
hours, minutes and seconds (don't worry for fractions of second). If v1 >= v2
then return nil, nothing, null, None or {-1, -1, -1} for C++.

Examples:

race(720, 850, 70) => [0, 32, 18]
race(80, 91, 37) => [3, 21, 49]
Note: you can see some other examples in "Your test cases".
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
  static vector<int> race_01(int v1, int v2, int g) {
    if (v1 >= v2) return {-1, -1, -1};
    int t = g * 3600 / (v2 - v1);
    return {t / 3600, t / 60 % 60, t % 60};
  };
  static vector<int> race_02(int v1, int v2, int g) {
    int d = v2 - v1;
    if (d <= 0) return {-1, -1, -1};
    int h = g / d;
    int r = g % d;
    int mn = r * 60 / d;
    int s = (r * 60 % d) * 60 / d;
    return vector<int>{h, mn, s};
  };
};

class TestCase {
 public:
  int v1;
  int v2;
  int g;
  vector<int> expected;
  TestCase(int v1_, int v2_, int g_, const vector<int> &expected_)
      : v1(v1_), v2(v2_), g(g_), expected(expected_) {
    // Constructor
  }
};

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

const vector<TestCase> set_gen(
    const function<vector<int>(int, int, int)> &race) {
  vector<TestCase> testcases;

  uniform_int_distribution<int> uni1(50, 750);
  uniform_int_distribution<int> uni2(60, 850);
  uniform_int_distribution<int> uni3(30, 150);

  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int v1 = uni1(gen);
    int v2 = uni2(gen);
    int g = uni3(gen);
    const vector<int> &expected = race(v1, v2, g);
    testcases.push_back(TestCase(v1, v2, g, expected));
  }
  return testcases;
}

void test(const function<vector<int>(int, int, int)> &race,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(race(testcase.v1, testcase.v2, testcase.g) == testcase.expected);
  }
}

unsigned long test_spd(const function<vector<int>(int, int, int)> &race,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) race(testcase.v1, testcase.v2, testcase.g);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<microseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.race_01);
  test(sol.race_01, testcases);
  cout << "race_01:\t" << test_spd(sol.race_01, testcases) << "ms" << endl;
  return 0;
}