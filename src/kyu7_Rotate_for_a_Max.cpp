/*
https://www.codewars.com/kata/rotate-for-a-max

Take a number: 56789. Rotate left, you get 67895.

Keep the first digit in place and rotate left the other digits: 68957.

Keep the first two digits in place and rotate the other ones: 68579.

Keep the first three digits and rotate left the rest: 68597. Now it is over
since keeping the first four it remains only one digit which rotated is itself.

You have the following sequence of numbers:

56789 -> 67895 -> 68957 -> 68579 -> 68597

and you must return the greatest: 68957.

Calling this function max_rot (or maxRot or ... depending on the language)

max_rot(56789) should return 68957
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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
#include "common.cpp"

using namespace std;

class Solution {
 public:
  static int64_t maxRot_01(int64_t n) {
    string n_str = to_string(n);
    size_t l = n_str.size();
    int64_t base0 = pow(10, l);
    int64_t base1 = 10;
    int64_t ret(n);
    for (size_t i = 1; i < l; ++i) {
      int64_t n_ = n / base0 * base0;
      n %= base0;
      base0 /= 10;
      n = n_ + n % base0 * 10 + n / base0;
      if (ret < n) ret = n;
    }
    return ret;
  }

  static int64_t maxRot_02(int64_t n) {
    string s = to_string(n);
    size_t l = s.size();
    int64_t ret = stoll(s);
    for (size_t i = 0; i < l - 1; i++) {
      rotate(s.begin() + i, s.begin() + 1 + i, s.end());
      ret = ret > stoll(s) ? ret : stoll(s);
    }
    return ret;
  }
};

class TestCase {
 public:
  const int64_t n;
  const int64_t expected;
  TestCase(int64_t n_, int64_t expected_) : n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<int64_t(int64_t)> &maxRot) {
  vector<TestCase> testcases;
  uniform_int_distribution<int64_t> uni1(1000000, 100000000);
  for (size_t i = 0; i < 100; ++i) {
    int64_t n = uni1(gen);
    int64_t expected = maxRot(n);
    testcases.push_back(TestCase(n, expected));
  }
  return testcases;
}

void test(const function<int64_t(int64_t)> &maxRot,
          const vector<TestCase> &testcases) {
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const int64_t actual = maxRot(testcase.n);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.n << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

uint64_t test_spd(const function<int64_t(int64_t)> &maxRot,
                  const vector<TestCase> &testcases, uint32_t n_ = 1000) {
  using namespace chrono;
  uint64_t elapsed = 0;
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    uint32_t n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) maxRot(testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.maxRot_01);
  cout << "test..." << endl;
  cout << "maxRot_01" << endl, test(sol.maxRot_01, testcases);
  cout << "maxRot_02" << endl, test(sol.maxRot_02, testcases);
  cout << "test_spd..." << endl;
  cout << "maxRot_01:\t" << test_spd(sol.maxRot_01, testcases) << "ms" << endl;
  cout << "maxRot_02:\t" << test_spd(sol.maxRot_02, testcases) << "ms" << endl;
  return 0;
}
