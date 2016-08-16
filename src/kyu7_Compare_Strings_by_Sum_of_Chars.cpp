/*
https://www.codewars.com/kata/576bb3c4b1abc497ec000065

Compare two strings by comparing the sum of their letter-Values (char-Value).
For comparing treat all letters as UpperCase.

Null-Strings should be treated as if they are empty strings.
If the string contains other characters than letters, treat the whole string as
it would be empty.

Examples:

"AD","BC" -> equal

"AD","DD" -> not equal

"gf","FG" -> equal

"zz1","" -> equal

"ZzZz", "ffPFF" -> equal

"kl", "lz" -> not equal

null, "" -> equal
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
#include "common.cpp"

using namespace std;

class Solution {
 public:
  static bool compare_01(const string &s1, const string &s2) {
    int i1{0};
    for (char c : s1) {
      c = toupper(c);
      if (c >= 'A' && c <= 'Z')
        i1 += c;
      else {
        i1 = 0;
        break;
      }
    }
    int i2{0};
    for (char c : s2) {
      c = toupper(c);
      if (c >= 'A' && c <= 'Z')
        i2 += c;
      else {
        i2 = 0;
        break;
      }
    }
    return i1 == i2;
  };

  static bool compare_02(const string &s1, const string &s2) {
    if (s1.empty() || s2.empty()) return true;
    int i1 = 0, i2 = 0;
    for (int i = 0; i < s1.length(); ++i) {
      if (!isalpha(s1.at(i))) {
        i1 = 0;
        break;
      }
      i1 += toupper(s1.at(i));
    }
    for (int i = 0; i < s2.length(); ++i) {
      if (!isalpha(s2.at(i))) {
        i2 = 0;
        break;
      }
      i2 += toupper(s2.at(i));
    }
    return i1 == i2;
  };

  static bool compare_03(const string &s1, const string &s2) {
    auto val = [](const string &s) -> int {
      int sum = 0;
      for (const char &c : s) {
        if (!isalpha(c)) return 0;
        sum += toupper(c);
      }
      return sum;
    };
    return val(s1) == val(s2);
  };
};

class TestCase {
 public:
  string s1;
  string s2;
  bool expected;
  TestCase(const string &s1_, const string &s2_, bool expected_)
      : s1(s1_), s2(s2_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<bool(const string &, const string &)> &compare) {
  vector<TestCase> testcases;
  const string set_letters{"abcdefABCDEF"};
  const string set{"1234abcdefABCDEF"};
  srand(time(0));
  for (int i = 10; i < 100; i++) {
    string s1;
    string s2;
    if (choice<bool>({true, false})) {
      s1 = rand_string(i, set);
      s2 = rand_string(i, set);
    } else {
      char letter1 = rand_char(set_letters);
      char letter2;
      do {
        letter2 = rand_char(set_letters);
      } while (letter1 == letter2);
      s1 = string(i - 1, toupper(letter1)) + letter2;
      s2 = letter2 + string(i - 1, tolower(letter1));
    }
    bool expected = compare(s1, s2);
    testcases.push_back(TestCase(s1, s2, expected));
  }
  return testcases;
}

void test(const function<bool(const string &, const string &)> &compare,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(compare(testcase.s1, testcase.s2) == testcase.expected);
  }
}

unsigned long test_spd(
    const function<bool(const string &, const string &)> &compare,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) compare(testcase.s1, testcase.s2);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.compare_01);
  test(sol.compare_01, testcases);
  test(sol.compare_02, testcases);
  test(sol.compare_03, testcases);
  cout << "compare_01:\t" << test_spd(sol.compare_01, testcases) << "ms"
       << endl;
  cout << "compare_02:\t" << test_spd(sol.compare_02, testcases) << "ms"
       << endl;
  cout << "compare_03:\t" << test_spd(sol.compare_03, testcases) << "ms"
       << endl;
  return 0;
}