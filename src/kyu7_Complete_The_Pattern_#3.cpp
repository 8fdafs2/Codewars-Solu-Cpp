/*
https://www.codewars.com/kata/complete-the-pattern-number-3-horizontal-image-of-number-2

Task:

You have to write a function pattern which creates the following pattern upto n
number of rows. If the Argument is 0 or a Negative Integer then it should return
"" i.e. empty string.

Pattern:

(n)
(n)(n-1)
(n)(n-1)(n-2)
................
.................
(n)(n-1)(n-2)....4
(n)(n-1)(n-2)....43
(n)(n-1)(n-2)....432
(n)(n-1)(n-2)....4321
Examples:

pattern(4):

4
43
432
4321
pattern(6):

6
65
654
6543
65432
654321
Note: There are no blank spaces

Hint: Use \n in string to jump to next line
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static string pattern_01(int n) {
    if (n < 1) return "";
    vector<string> seq(n);
    for (int i = 0; i < n; i++) seq[i] = to_string(n - i);
    string ret = "";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++) ret += seq[j];
      ret += "\n";
    }
    return ret.substr(0, ret.length() - 1);
  };

  static string pattern_02(int n) {
    if (n < 1) return "";
    stringstream ss;
    for (int j = 0; j < n; j++) {
      for (int i = n; i > n - j - 1; i--) ss << i;
      ss << "\n";
    }
    string ret = ss.str();
    return ret.substr(0, ret.size() - 1);
  };

  static string pattern_03(int n) {
    if (n < 1) return "";
    vector<int> seq(n);
    for (int i = 0; i < n; i++) seq[i] = n - i;
    string ret = "";
    for (int i = n - 1; i > -1; i--) {
      ostringstream oss_;
      copy(seq.begin(), seq.end() - i, ostream_iterator<int>(oss_));
      ret += oss_.str() + "\n";
    }
    ret.erase(ret.length() - 1);
    return ret;
  };
};

class TestCase {
 public:
  int n;
  string expected;
  TestCase(const int n_, const string &expected_) : n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(int)> &pattern) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int n = 0; n < 50; n++) {
    string expected = pattern(n);
    testcases.push_back(TestCase(n, expected));
  }
  return testcases;
}

void test(const function<string(int)> &pattern,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    // cout << pattern(testcase.n) << endl;
    // cout << testcase.expected << endl;
    assert(pattern(testcase.n) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(int)> &pattern,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) pattern(testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<microseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.pattern_01);
  test(sol.pattern_01, testcases);
  test(sol.pattern_02, testcases);
  test(sol.pattern_03, testcases);
  cout << "pattern_01:\t" << test_spd(sol.pattern_01, testcases) << "ms"
       << endl;
  cout << "pattern_02:\t" << test_spd(sol.pattern_02, testcases) << "ms"
       << endl;
  cout << "pattern_03:\t" << test_spd(sol.pattern_03, testcases) << "ms"
       << endl;
  return 0;
}