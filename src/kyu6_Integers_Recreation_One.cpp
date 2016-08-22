/*
https://www.codewars.com/kata/integers-recreation-one

Divisors of 42 are : 1, 2, 3, 6, 7, 14, 21, 42. These divisors squared are: 1,
4, 9, 36, 49, 196, 441, 1764. The sum of the squared divisors is 2500 which is
50 * 50, a square!

Given two integers m, n (1 <= m <= n) we want to find all integers between m and
n whose sum of squared divisors is itself a square. 42 is such a number.

The result will be an array of arrays, each subarray having two elements, first
the number whose squared divisors is a square and then the sum of the squared
divisors.
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
  static string listSquared_01(int m, int n) {
    string ret;
    for (int i = m; i <= n; i++) {
      int sum = 0;
      for (int j = 1; j <= i; j++)
        if (i % j == 0) sum += j * j;
      double sqrt_sum = sqrt(sum);
      if (floor(sqrt_sum) == sqrt_sum)
        ret += "{" + to_string(i) + ", " + to_string(sum) + "}, ";
    };
    return "{" + ret.substr(0, ret.size() - 2) + "}";
  };

  static string listSquared_02(int m, int n) {
    ostringstream oss;
    if (m == 1) {
      oss << "{1, 1}, ";
      ++m;
    }
    for (int i = m; i <= n; i++) {
      int sum = 1 + i * i;
      double sqrt_i_f = sqrt(i);
      int sqrt_i_i = floor(sqrt_i_f);
      if (sqrt_i_f == sqrt_i_i) sum += i * i;
      for (int j = 2; j <= sqrt_i_i; j++)
        if (i % j == 0) sum += j * j + pow(i / j, 2);
      double sqrt_sum = sqrt(sum);
      if (floor(sqrt_sum) == sqrt_sum) oss << "{" << i << ", " << sum << "}, ";
    };
    string ret = oss.str();
    return "{" + ret.substr(0, ret.size() - 2) + "}";
  };
};

class TestCase {
 public:
  int m;
  int n;
  string expected;
  TestCase(int m_, int n_, string &expected_)
      : m(m_), n(n_), expected(expected_) {
    // Constructor
  }
};

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

const vector<TestCase> set_gen(const function<string(int, int)> &listSquared) {
  vector<TestCase> testcases;
  for (int i = 0; i < 10; i++) {
    uniform_int_distribution<int> uni1(200, 1000);
    int m = uni1(gen);
    uniform_int_distribution<int> uni2(1100, 8000);
    int n = uni2(gen);
    string expected = listSquared(m, n);
    testcases.push_back(TestCase(m, n, expected));
  }
  return testcases;
}

void test(const function<string(int, int)> &listSquared,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(listSquared(testcase.m, testcase.n) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(int, int)> &listSquared,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) listSquared(testcase.m, testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.listSquared_01);
  test(sol.listSquared_01, testcases);
  test(sol.listSquared_02, testcases);
  cout << "listSquared_01:\t" << test_spd(sol.listSquared_01, testcases, 10)
       << "ms" << endl;
  cout << "listSquared_02:\t" << test_spd(sol.listSquared_02, testcases, 10)
       << "ms" << endl;
  return 0;
}
