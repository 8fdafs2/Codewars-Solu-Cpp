/*

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
#include <vector>

using namespace std;

class Solution {
 public:
  static string subsol_01(int input) { return to_string(input); };
};

class TestCase {
 public:
  int input;
  string expected;
  TestCase(const int input_, const string &expected_)
      : input(input_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(int)> &subsol) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int input = rand() % 100;
    string expected = subsol(input);
    testcases.push_back(TestCase(input, expected));
  }
  return testcases;
}

void test(const function<string(int)> &subsol,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(subsol(testcase.input) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(int)> &subsol,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
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
  test(sol.subsol_01, testcases);
  cout << "subsol_01:\t" << test_spd(sol.subsol_01, testcases) << "ms" << endl;
  return 0;
}