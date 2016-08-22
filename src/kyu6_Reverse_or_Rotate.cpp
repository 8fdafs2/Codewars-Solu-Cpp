/*
https://www.codewars.com/kata/reverse-or-rotate

The input is a string str of digits. Cut the string into chunks of size sz
(ignore the last chunk if its size is less than sz).

If a chunk represents an integer such as the sum of the cubes of its digits is
divisible by 2, reverse it; otherwise rotate it to the left by one position. Put
together these modified chunks and return the result as a string.

If

sz is <= 0 or if str is empty return ""
sz is greater (>) than the length of str it is impossible to take a chunk of
size sz hence return "".
Examples:
revrot("123456987654", 6) --> "234561876549"
revrot("123456987653", 6) --> "234561356789"
revrot("66443875", 4) --> "44668753"
revrot("66443875", 8) --> "64438756"
revrot("664438769", 8) --> "67834466"
revrot("123456779", 8) --> "23456771"
revrot("", 8) --> ""
revrot("123456779", 0) --> ""
*/

#include "common.cpp"
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
  static string revRot_01(const string &s, unsigned int sz) {
    string ret;
    if (sz < 1 || s.empty())
      return ret;
    int l = s.size();
    if (sz > l)
      return ret;
    vector<string> vs;
    int p{0};
    do {
      vs.push_back(s.substr(p, sz));
      p += sz;
    } while (p + sz <= l);
    for (auto &s : vs) {
      int num{0};
      for (auto &c : s)
        num += c - '0';
      if (num % 2 == 0)
        reverse(s.begin(), s.end());
      else
        rotate(s.begin(), s.begin() + 1, s.end());
      ret += s;
    }
    return ret;
  }

  static string revRot_02(const string &s, unsigned int sz) {
    if (sz <= 0 || s.empty() || sz > s.length())
      return "";
    string x = s.substr(0, sz);
    bool p = true;
    for (const char &c : x)
      if (c % 2 == 1) // '0' == 48, so 'digit' is even iff digit is even
        p = !p;
    if (p) {
      reverse(x.begin(), x.end());
      return x + revRot_02(s.substr(sz), sz);
    }
    return x.substr(1) + x[0] + revRot_02(s.substr(sz), sz);
  }
};

class TestCase {
public:
  const string s;
  const unsigned int sz;
  const string expected;
  TestCase(const string &s_, unsigned int sz_, const string &expected_)
      : s(s_), sz(sz_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase>
set_gen(const function<string(const string &, unsigned int)> &revRot) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(15, 100);
  uniform_int_distribution<unsigned int> uni2(2, 5);
  for (int i = 0; i < 100; ++i) {
    int l = uni1(gen);
    string s = rand_string(l, '0123456789');
    unsigned int sz = uni2(gen);
    string expected = revRot(s, sz);
    testcases.push_back(TestCase(s, sz, expected));
  }
  return testcases;
}

void test(const function<string(const string &, unsigned int)> &revRot,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const string &actual = revRot(testcase.s, testcase.sz);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "	!!Assertion Failed!!" << endl;
      cout << "	in: " << testcase.s << " | " << testcase.sz << endl;
      cout << "	out:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

unsigned long
test_spd(const function<string(const string &, unsigned int)> &revRot,
         const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--)
      revRot(testcase.s, testcase.sz);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.revRot_01);
  cout << "test..." << endl;
  cout << "revRot_01" << endl, test(sol.revRot_01, testcases);
  cout << "revRot_02" << endl, test(sol.revRot_02, testcases);
  cout << "test_spd..." << endl;
  cout << "revRot_01:	" << test_spd(sol.revRot_01, testcases) << "ms" << endl;
  cout << "revRot_02:	" << test_spd(sol.revRot_02, testcases) << "ms" << endl;
  return 0;
}
