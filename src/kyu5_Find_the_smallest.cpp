/*
https://www.codewars.com/kata/find-the-smallest

You have a number n consisting of digits. You can do at most one operation:
Choosing the index of a digit in the number, remove this digit at that index and
insert it back to another place in the number.

Doing so, find the smallest number you can get.

Task:

Return an array or a tuple depending on the language (see "Your Test Cases"
Haskell) with

1) the smallest number you got
2) the index i of the digit d you took, i as small as possible
3) the index j (as small as possible) where you insert this digit d to have the
smallest number.
Example:

smallest(261235) --> [126235, 2, 0]
126235 is the smallest number gotten by taking 1 at index 2 and putting it at
index 0

smallest(209917) --> [29917, 0, 1]

[29917, 1, 0] could be a solution too but index `i` in [29917, 1, 0] is greater
than
index `i` in [29917, 0, 1].
29917 is the smallest number gotten by taking 2 at index 0 and putting it at
index 1 which gave 029917 which is the number 29917.

smallest(1000000) --> [1, 0, 6]
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
  static vector<long long> smallest_01(long long n) {
    string n_str{to_string(n)};
    long long l = n_str.size();
    for (auto d : "0123456789") {
      long long i = n_str.rfind(d);
      if (i > 0 && i < l) {
        bool tocontinue = true;
        for (long long k = i; k >= 0; --k)
          if (n_str[k] > d)
            tocontinue = false;
        if (tocontinue)
          continue;
        for (long long j = 0; j < i; ++j) {
          if (n_str[j] >= d) { // i != j
            // i < j
            long long i_{i};
            while (n_str[i_ - 1] == d)
              --i_;
            n_str.erase(i_, 1);
            n_str.insert(j, 1, d);
            vector<long long> ret_01{stoll(n_str), i_, j};
            // i > j ?
            for (i = i_, n_str = to_string(n); n_str[j] == d; ++j)
              ;
            if (!(j + 1 == i ||
                  (n_str[j + 1] == d && n_str[j + 2] <= n_str[j])))
              return ret_01;
            // i > j
            for (i = j, d = n_str[i], j = i + 1; j < l && n_str[j] <= d; ++j)
              ;
            while (n_str[j - 1] == d)
              --j;
            n_str.erase(i, 1);
            n_str.insert(j - 1, 1, d);
            vector<long long> ret_02{stoll(n_str), i, j - 1};
            if (ret_01[0] < ret_02[0])
              return ret_01;
            if (ret_01[0] > ret_02[0])
              return ret_02;
            if (ret_01[1] < ret_02[1])
              return ret_01;
            return ret_02;
          }
        }
        // i == j
        return {n, 0, 0};
      }
    }
  }

  static vector<long long> smallest_02(long long n) {
    string s = to_string(n), tmp = s;
    vector<long long> mem = {n, 0, 0};
    unsigned int l = s.length();
    for (unsigned int i = 0; i < l; i++) {
      char c = s[i];
      string str1 = s.substr(0, i) + s.substr(i + 1, l - (i + 1));
      for (unsigned int j = 0; j < l; j++) {
        string str2 = str1.substr(0, j) + c + str1.substr(j, str1.length() - j);
        if (str2 < tmp) {
          tmp = str2;
          mem = {stoll(tmp), i, j};
        }
      }
    }
    return mem;
  }
};

class TestCase {
public:
  const long long n;
  const vector<long long> expected;
  TestCase(long long n_, const vector<long long> &expected_)
      : n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase>
set_gen(const function<vector<long long>(long long)> &smallest) {
  vector<TestCase> testcases;
  uniform_int_distribution<long long> uni1(10000000, 100000000);
  for (int i = 0; i < 100; ++i) {
    long long n = uni1(gen);
    vector<long long> expected = smallest(n);
    testcases.push_back(TestCase(n, expected));
  }
  return testcases;
}

void test(const function<vector<long long>(long long)> &smallest,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const vector<long long> &actual = smallest(testcase.n);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.n << endl;
      cout << "\tout:" << vtos(actual) << " vs. " << vtos(testcase.expected)
           << endl;
    }
  }
}

unsigned long test_spd(const function<vector<long long>(long long)> &smallest,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--)
      smallest(testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.smallest_01);
  cout << "test..." << endl;
  cout << "smallest_01" << endl, test(sol.smallest_01, testcases);
  cout << "smallest_02" << endl, test(sol.smallest_02, testcases);
  cout << "test_spd..." << endl;
  cout << "smallest_01:\t" << test_spd(sol.smallest_01, testcases) << "ms"
       << endl;
  cout << "smallest_02:\t" << test_spd(sol.smallest_02, testcases) << "ms"
       << endl;
  return 0;
}
