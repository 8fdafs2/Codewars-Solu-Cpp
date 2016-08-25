/*

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
  static string subsol_01(uint32_t input) { return to_string(input); }
};

class TestCase {
 public:
  const uint32_t input;
  const string expected;
  TestCase(uint32_t input_, const string &expected_)
      : input(input_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(uint32_t)> &subsol) {
  vector<TestCase> testcases;
  uniform_int_distribution<uint32_t> uni1(0, 100);
  for (size_t i = 0; i < 100; ++i) {
    uint32_t input = uni1(gen);
    string expected = subsol(input);
    testcases.push_back(TestCase(input, expected));
  }
  return testcases;
}

void test(const function<string(uint32_t)> &subsol,
          const vector<TestCase> &testcases) {
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const string &actual = subsol(testcase.input);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.input << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

uint64_t test_spd(const function<string(int32_t)> &subsol,
                  const vector<TestCase> &testcases, uint32_t n_ = 1000) {
  using namespace chrono;
  uint64_t elapsed = 0;
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    uint32_t n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) subsol(testcase.input);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.subsol_01);
  cout << "test..." << endl;
  cout << "subsol_01" << endl, test(sol.subsol_01, testcases);
  cout << "test_spd..." << endl;
  cout << "subsol_01:\t" << test_spd(sol.subsol_01, testcases) << "ms" << endl;
  return 0;
}
