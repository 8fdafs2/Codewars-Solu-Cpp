/*
https://www.codewars.com/kata/577e277c9fb2a5511c00001d

You get a "text" and have to shift the vowels by "n" positions to the right.
(Negative value for n should shift to the left.)
"Position" means the vowel's position if taken as one item in a list of all
vowels within the string.
A shift by 1 would mean, that every vowel shifts to the place of the next vowel.

Shifting over the edges of the text should continue at the other edge.

Example:

text = "This is a test!"
n = 1
output = "Thes is i tast!"

text = "This is a test!"
n = 3
output = "This as e tist!"

If text is null or empty return exactly this value.
Vowels are "a,e,i,o,u".


Have fun coding it and please don't forget to vote and rank this kata! :-)

I have created other katas. Have a look if you like coding and challenges.
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
  static string vowelShift_01(const string &text, int n) {
    string ret(text);
    int l = text.size();
    if (l < 2 || n == 0) return ret;
    const string vowels{"aAeEiIoOuU"};
    vector<pair<int, char>> tab;
    for (int i = 0; i < l; ++i)
      if (vowels.find(text[i]) != string::npos) tab.push_back({i, text[i]});
    l = tab.size();
    if (l < 1) return ret;
    while (n < 0) n += l;
    for (int i = 0; i < l; ++i) ret[tab[(i + n) % l].first] = tab[i].second;
    return ret;
  };
  static string vowelShift_02(const string &text, int n) {
    string ret(text);
    int l = text.size();
    if (l < 2 || n == 0) return ret;
    auto vowel = [](char c) -> bool {
      c = tolower(c);
      return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };
    vector<pair<int, char>> vowels;
    for (int i = 0; i < l; i++)
      if (vowel(text.at(i))) vowels.push_back(make_pair(i, text.at(i)));
    if (vowels.empty()) return ret;
    l = vowels.size();
    for (int i = 0; i < l; i++) {
      int replacement = i - n;
      while (replacement >= l) replacement -= l;
      while (replacement < 0) replacement += l;
      ret.at(vowels[i].first) = vowels[replacement].second;
    }
    return ret;
  };
};

class TestCase {
 public:
  const string text;
  const int n;
  const string expected;
  TestCase(const string &text_, int n_, const string &expected_)
      : text(text_), n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<string(const string &, int)> &vowelShift) {
  vector<TestCase> testcases;
  for (int i = 10; i < 100; ++i) {
    string text = rand_string(i);
    int n = i / 10;
    string expected = vowelShift(text, n);
    testcases.push_back(TestCase(text, n, expected));
  }
  return testcases;
}

void test(const function<string(const string &, int)> &vowelShift,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const string &actual = vowelShift(testcase.text, testcase.n);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.text << " | " << testcase.n << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

int long test_spd(const function<string(const string &, int)> &vowelShift,
                  const vector<TestCase> &testcases, unsigned n_ = 1000) {
  using namespace chrono;
  int long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) vowelShift(testcase.text, testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.vowelShift_01);
  cout << "test..." << endl;
  cout << "vowelShift_01" << endl, test(sol.vowelShift_01, testcases);
  cout << "vowelShift_02" << endl, test(sol.vowelShift_02, testcases);
  cout << "test_spd..." << endl;
  cout << "vowelShift_01:\t" << test_spd(sol.vowelShift_01, testcases) << "ms"
       << endl;
  return 0;
}