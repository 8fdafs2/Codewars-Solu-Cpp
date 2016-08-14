/*
https://www.codewars.com/kata/rectangle-into-squares

The drawing below gives an idea of how to cut a given "true" rectangle into
squares ("true" rectangle meaning that the two dimensions are different).

alternative text

Can you translate this drawing into an algorithm?

You will be given two dimensions

a positive integer length (parameter named lng)
a positive integer width (parameter named wdth)
You will return an array with the size of each of the squares.

Examples

  sqInRect(5, 3) should return {3, 2, 1, 1}
  sqInRect(3, 5) should return {3, 2, 1, 1}
Note: lng == wdth as a starting case would be an entirely different problem and
the drawing is planned to be interpreted with lng != wdth. See kata, Square into
Squares. Protect trees!.

When the initial parameters are so that lng == wdth, the solution [lng] would be
the most obvious but not in the spirit of this kata so, in that case, return
None/nil/null/Nothing/{} with C++.

Examples:

  sqInRect(5, 5) should return {}
*/

#include <algorithm>
#include <cassert>
#include <chrono>
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
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  static vector<int> sqInRect_01(int l, int w) {
    vector<int> ret;
    if (w == l) return ret;
    if (w > l) swap(l, w);
    while (w > 0) {
      ret.push_back(w);
      int t = w;
      w = l - w;
      l = t;
      if (w > l) swap(l, w);
    }
    return ret;
  };

  static vector<int> sqInRect_02(int l, int w) {
    if (l == w) return vector<int>();
    if (l < w) swap(l, w);
    if (l % w == 0) return vector<int>(l / w, w);
    vector<int> ans = sqInRect_02(l - w, w);
    ans.insert(ans.begin(), w);
    return ans;
  };

  static vector<int> sqInRect_03(int l, int w) {
    if (l == w) return {};
    vector<int> arr;
    while (l > 0 && w > 0) {
      if (l > w) {
        arr.push_back(w);
        l -= w;
      } else {
        arr.push_back(l);
        w -= l;
      }
    }
    return arr;
  };
};

class TestCase {
 public:
  int l;
  int w;
  vector<int> expected;
  TestCase(int l_, int w_, const vector<int> &expected_)
      : l(l_), w(w_), expected(expected_) {
    // Constructor
  }
};

random_device rd;
mt19937 rng(rd());

const vector<TestCase> set_gen(
    const function<vector<int>(int, int)> &sqInRect) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(200, 750);
  for (int i = 0; i < 100; i++) {
    int l = uni1(rng);
    int w = uni1(rng);
    vector<int> expected = sqInRect(l, w);
    testcases.push_back(TestCase(l, w, expected));
  }
  return testcases;
}

void test(const function<vector<int>(int, int)> &sqInRect,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(sqInRect(testcase.l, testcase.w) == testcase.expected);
  }
}

unsigned long test_spd(const function<vector<int>(int, int)> &sqInRect,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) sqInRect(testcase.l, testcase.w);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.sqInRect_01);
  test(sol.sqInRect_01, testcases);
  test(sol.sqInRect_02, testcases);
  test(sol.sqInRect_03, testcases);
  cout << "sqInRect_01:\t" << test_spd(sol.sqInRect_01, testcases) << "ms"
       << endl;
  cout << "sqInRect_02:\t" << test_spd(sol.sqInRect_02, testcases) << "ms"
       << endl;
  cout << "sqInRect_03:\t" << test_spd(sol.sqInRect_03, testcases) << "ms"
       << endl;
  return 0;
}