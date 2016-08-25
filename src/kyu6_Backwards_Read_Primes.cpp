/*
https://www.codewars.com/kata/backwards-read-primes

Backwards Read Primes are primes that when read backwards in base 10 (from right
to left) are a different prime. (This rules out primes which are palindromes.)

Examples:
13 17 31 37 71 73 are Backwards Read Primes
13 is such because it's prime and read from right to left writes 31 which is
prime too. Same for the others.

Task

Find all Backwards Read Primes between two positive given numbers (both
inclusive), the second one being greater than the first one. The resulting array
or the resulting string will be ordered following the natural order of the prime
numbers.

backwardsPrime(2, 100) => "13 17 31 37 71 73 79 97"
backwardsPrime(9900, 10000) => "9923 9931 9941 9967"
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
  static bool is_prime(int64_t n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    uint32_t root = sqrt(n);
    for (size_t i = 3; i < root + 1; i += 2)
      if ((n % i) == 0) return false;
    return true;
  }

  static string backwardsPrime_01(int64_t start, int64_t end) {
    string ret;
    for (int64_t i = start; i <= end; ++i) {
      string i_str = to_string(i);
      reverse(i_str.begin(), i_str.end());
      int64_t i_reversed = stoll(i_str);
      if (i != i_reversed && is_prime(i) && is_prime(i_reversed))
        ret += to_string(i) + " ";
    }
    return ret.substr(0, ret.size() - 2);
  }

  static void reverse_02(int64_t p, int64_t &rp) {
    rp = rp * 10 + p % 10;
    p = p / 10;
    if (p != 0) reverse_02(p, rp);
  }
  static string backwardsPrime_02(int64_t start, int64_t end) {
    string ret;
    for (int64_t i = start; i <= end; ++i) {
      int64_t i_reversed = 0;
      reverse_02(i, i_reversed);
      if (i != i_reversed && is_prime(i) && is_prime(i_reversed))
        ret += to_string(i) + " ";
    }
    return ret.substr(0, ret.size() - 2);
  }

  static int64_t reverse_03(int64_t n) {
    int64_t ret = 0;
    while (n != 0) {
      ret = ret * 10 + n % 10;
      n /= 10;
    }
    return ret;
  }
  static string backwardsPrime_03(int64_t start, int64_t end) {
    string ret;
    for (int64_t i = start; i <= end; ++i) {
      int64_t i_reversed = reverse_03(i);
      if (i != i_reversed && is_prime(i) && is_prime(i_reversed))
        ret += to_string(i) + " ";
    }
    return ret.substr(0, ret.size() - 2);
  }
};

class TestCase {
 public:
  const int64_t start;
  const int64_t end;
  const string expected;
  TestCase(int64_t start_, int64_t end_, const string &expected_)
      : start(start_), end(end_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<string(int64_t, int64_t)> &backwardsPrime) {
  vector<TestCase> testcases;
  uniform_int_distribution<int64_t> uni1(100, 500);
  uniform_int_distribution<int64_t> uni2(10, 50);
  for (size_t i = 0; i < 100; ++i) {
    int64_t start = uni1(gen);
    int64_t end = start * uni2(gen);
    string expected = backwardsPrime(start, end);
    testcases.push_back(TestCase(start, end, expected));
  }
  return testcases;
}

void test(const function<string(int64_t, int64_t)> &backwardsPrime,
          const vector<TestCase> &testcases) {
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const string &actual = backwardsPrime(testcase.start, testcase.end);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.start << " | " << testcase.end << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

uint64_t test_spd(const function<string(int64_t, int64_t)> &backwardsPrime,
                  const vector<TestCase> &testcases, uint32_t n_ = 10) {
  using namespace chrono;
  uint64_t elapsed = 0;
  for (size_t i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    uint32_t n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) backwardsPrime(testcase.start, testcase.end);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.backwardsPrime_01);
  cout << "test..." << endl;
  cout << "backwardsPrime_01" << endl, test(sol.backwardsPrime_01, testcases);
  cout << "backwardsPrime_02" << endl, test(sol.backwardsPrime_02, testcases);
  cout << "backwardsPrime_03" << endl, test(sol.backwardsPrime_03, testcases);
  cout << "test_spd..." << endl;
  cout << "backwardsPrime_01:\t" << test_spd(sol.backwardsPrime_01, testcases)
       << "ms" << endl;
  cout << "backwardsPrime_02:\t" << test_spd(sol.backwardsPrime_02, testcases)
       << "ms" << endl;
  cout << "backwardsPrime_03:\t" << test_spd(sol.backwardsPrime_03, testcases)
       << "ms" << endl;
  return 0;
}
