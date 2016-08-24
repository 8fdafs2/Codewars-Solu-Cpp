/*
https://www.codewars.com/kata/product-of-consecutive-fib-numbers

The Fibonacci numbers are the numbers in the following integer sequence (Fn):

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, ...
such as

F(n) = F(n-1) + F(n-2) with F(0) = 0 and F(1) = 1.
Given a number, say prod (for product), we search two Fibonacci numbers F(n) and
F(n+1) verifying

F(n) * F(n+1) = prod.
Your function productFib takes an integer (prod) and returns an array:

if F(n) * F(n+1) = prod or returns

if you don't find two consecutive F(m) verifying F(m) * F(m+1) = prod. F(m) will
be the smallest one such as F(m) * F(m+1) > prod.

Examples

Note: Not useful here but we can tell how to choose the number n up to which to
go: we can use the "golden ratio" phi which is (1 + sqrt(5))/2 knowing that F(n)
is asymptotic to: phi^n / sqrt(5). That gives a possible upper bound to n.

References

http://en.wikipedia.org/wiki/Fibonacci_number

http://oeis.org/A000045
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

typedef unsigned long long ull;

class Solution {
 public:
  static vector<ull> productFib_01(ull prod) {
    double sqrt5 = sqrt(5);
    double gr = (1 + sqrt5) * 0.5;
    int n = round((log(5 * prod) / log(gr) - 1) * 0.5);
    ull fn = round(pow(gr, n) / sqrt5);
    ull fn1 = round(fn * gr);
    while (fn * fn1 < prod) {
      fn = fn1;
      fn1 = round(fn * gr);
    }
    return {fn, fn1, fn * fn1 == prod};
  }

  static vector<ull> productFib_02(ull prod) {
    ull fib0 = 0ULL, fib1 = 1ULL;
    while (fib0 * fib1 < prod) {
      ull fib = fib0 + fib1;
      fib0 = fib1;
      fib1 = fib;
    }
    return vector<ull>{fib0, fib1, fib0 * fib1 == prod};
  }
};

class TestCase {
 public:
  const ull prod;
  const vector<ull> expected;
  TestCase(ull prod_, const vector<ull> &expected_)
      : prod(prod_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<vector<ull>(ull)> &productFib) {
  vector<TestCase> testcases;
  uniform_int_distribution<ull> uni1(100000000000, 1000000000000);
  for (int i = 0; i < 1000; ++i) {
    ull prod = uni1(gen);
    vector<ull> expected = productFib(prod);
    testcases.push_back(TestCase(prod, expected));
  }
  return testcases;
}

void test(const function<vector<ull>(ull)> &productFib,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const vector<ull> &actual = productFib(testcase.prod);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.prod << endl;
      cout << "\tout:" << vtos(actual) << " vs. " << vtos(testcase.expected)
           << endl;
    }
  }
}

unsigned long test_spd(const function<vector<ull>(ull)> &productFib,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) productFib(testcase.prod);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.productFib_01);
  cout << "test..." << endl;
  cout << "productFib_01" << endl, test(sol.productFib_01, testcases);
  cout << "productFib_02" << endl, test(sol.productFib_02, testcases);
  cout << "test_spd..." << endl;
  cout << "productFib_01:\t" << test_spd(sol.productFib_01, testcases) << "ms"
       << endl;
  cout << "productFib_02:\t" << test_spd(sol.productFib_02, testcases) << "ms"
       << endl;
  return 0;
}