/*
https://www.codewars.com/kata/is-my-friend-cheating

A friend of mine takes a sequence of numbers from 1 to n (where n > 0).
Within that sequence, he chooses two numbers, a and b.
He says that the product of a and b should be equal to the s of all numbers in
the sequence, excluding a and b.
Given a number n, could you tell me the numbers he excluded from the sequence?
The function takes the parameter: n (don't worry, n is always strictly greater
than 0 and small enough so we shouldn't have overflow) and returns an array of
the form:

[(a, b), ...] or [[a, b], ...] or {{a, b}, ...} or or [{a, b}, ...]
with all (a, b) which are the possible removed numbers in the sequence 1 to n.

[(a, b), ...] or [[a, b], ...] or {{a, b}, ...} or ...will be sorted in
increasing order of the "a".

It happens that there are several possible (a, b). The function returns an empty
array if no possible numbers are found which will prove that my friend has not
told the truth!

Examples:

removNb(26) should return { {15, 21}, {21, 15} }
removNb(100) should return an array of size 0
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
  static vector<vector<long long>> removNb_01(long long n) {
    vector<vector<long long>> ret;
    long long a{(((1 + n) * n) >> 1) - 2};
    long long b{3};
    while (b <= n + 1) {
      if (a % b == 0 && b * n >= a) ret.push_back({b - 1, a / b});
      ++b;
      --a;
    }
    return ret;
  }

  static vector<vector<long long>> removNb_02(long long n) {
    vector<vector<long long>> ret;
    long long s = n * (n + 1) / 2;
    for (long long i = 1; i <= n; ++i) {
      long long j = (s - i) / (i + 1);
      if (j <= n && i * j == s - i - j) {
        ret.push_back({i, j});
      }
    }
    return ret;
  }

  static vector<vector<long long>> removNb_03(long long n) {
    vector<vector<long long>> ret;
    long long s = n * (n + 1) / 2;
    long long m = (n * n - n) / (2 * n + 2);
    for (long long i = m; i <= n; i++) {
      long long j = (n * n + n - 2.0 * i) / (2 * i + 2);
      if (i * j == s - i - j) ret.push_back({i, j});
    }
    return ret;
  }

  static vector<vector<long long>> removNb_04(long long n) {
    vector<vector<long long>> ret;
    long long s = n * (n + 1) / 2;
    long long i = n / 2;
    // long long i = (sqrt(3 + 4 * s) - 3) / 2;
    while (i <= n) {
      long long b = s - i;
      if (b % (i + 1) == 0) ret.push_back({i, b / (i + 1)});
      ++i;
    }
    return ret;
  }
};

class TestCase {
 public:
  long long n;
  vector<vector<long long>> expected;
  TestCase(long long n_, const vector<vector<long long>> &expected_)
      : n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<vector<vector<long long>>(long long)> &removNb) {
  vector<TestCase> testcases;
  for (long long n = 100000; n < 200000; n += 1000) {
    vector<vector<long long>> expected = removNb(n);
    testcases.push_back(TestCase(n, expected));
  }
  return testcases;
}

void test(const function<vector<vector<long long>>(long long)> &removNb,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(removNb(testcase.n) == testcase.expected);
  }
}

unsigned long test_spd(
    const function<vector<vector<long long>>(long long)> &removNb,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) removNb(testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.removNb_01);
  test(sol.removNb_01, testcases);
  test(sol.removNb_02, testcases);
  test(sol.removNb_03, testcases);
  test(sol.removNb_04, testcases);
  cout << "removNb_01:\t" << test_spd(sol.removNb_01, testcases, 10) << "ms"
       << endl;
  cout << "removNb_02:\t" << test_spd(sol.removNb_02, testcases, 10) << "ms"
       << endl;
  cout << "removNb_03:\t" << test_spd(sol.removNb_03, testcases, 10) << "ms"
       << endl;
  cout << "removNb_04:\t" << test_spd(sol.removNb_04, testcases, 10) << "ms"
       << endl;
  return 0;
}