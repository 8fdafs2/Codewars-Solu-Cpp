/*
https://www.codewars.com/kata/up-and-down

You are given a string s made up of substring s(1), s(2), ..., s(n) separated by
whitespaces. Example: "after be arrived two My so"

Task

Return a string t having the following property:

length t(O) <= length t(1) >= length t(2) <= length t(3) >= length t(4) .... (P)

where the t(i) are the substring of s; you must respect the following rule:

at each step from left to right, you can only move either already consecutive
strings or strings that became consecutive after a previous move. The number of
moves should be minimum.

Let us go with our example:

The length of "after" is greater than the length of "be". Let us move them ->"be
after arrived two My so"

The length of "after" is smaller than the length of "arrived". Let us move them
-> "be arrived after two My so"

The length of "after" is greater than the length of "two" ->"be arrived two
after My so"

The length of "after" is greater than the length of "My". Good! Finally the
length of "My" and "so" are the same, nothing to do. At the end of the process,
the substrings s(i) verify:

length s(0) <= length s(1) >= length s(2) <= length s(3) >= length (s4) <=
length (s5)

Hence given a string s of substrings s(i) the function arrange with the previous
process should return a unique string t having the property (P).

It is kind of roller coaster or up and down. When you have property (P), to make
the result more "up and down" visible t(0), t(2), ... will be lower cases and
the others upper cases.

arrange("after be arrived two My so") should return "be ARRIVED two AFTER my SO"
Notes:

The string "My after be arrived so two" has the property (P) but can't be
obtained by the described process so it won't be accepted as a result. The
property (P) doesn't give unicity by itself.
Process: go from left to right, move only consecutive strings when needed.
For the first fixed tests the needed number of moves to get property (P) is
given as a comment so that you can know if your process follows the rule.
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
  static string arrange_01(const string &s) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, ' ')) elems.push_back(item);
    int l = elems.size();
    if (l < 1) return "";
    for (int i = 0; i < l - 1; ++i)
      if (i % 2 == 0) {
        if (elems[i].size() > elems[i + 1].size()) swap(elems[i], elems[i + 1]);
      } else {
        if (elems[i].size() < elems[i + 1].size()) swap(elems[i], elems[i + 1]);
      }
    ss.clear();
    ss.str("");
    for (int i = 0; i < l; ++i) {
      if (i != 0) ss << " ";
      transform(elems[i].begin(), elems[i].end(), elems[i].begin(),
                i % 2 == 0 ? ::tolower : ::toupper);
      ss << elems[i];
    }
    return ss.str();
  };
};

class TestCase {
 public:
  int input;
  string expected;
  TestCase(int input_, const string &expected_)
      : input(input_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(int)> &subsol) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(0, 100);
  for (int i = 0; i < 100; i++) {
    int input = uni1(gen);
    string expected = subsol(input);
    testcases.push_back(TestCase(input, expected));
  }
  return testcases;
}

void test(const function<string(int)> &subsol,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    const string &actual = subsol(testcase.input);
    assert(subsol(testcase.input) == testcase.expected);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.input << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
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
  cout << "test..." << endl;
  cout << "subsol_01" << endl, test(sol.subsol_01, testcases);
  cout << "test_spd..." << endl;
  cout << "subsol_01:\t" << test_spd(sol.subsol_01, testcases) << "ms" << endl;
  return 0;
}