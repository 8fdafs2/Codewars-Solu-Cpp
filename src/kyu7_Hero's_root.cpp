/*
https://www.codewars.com/kata/heros-root

One of the first algorithm used for approximating the integer square root of a
positive integer n is known as "Hero's method", named after the first-century
Greek mathematician Hero of Alexandria who gave the first description of the
method. Hero's method can be obtained from Newton's method which came 16
centuries after.

We approximate the square root of a number n by taking an initial guess x, an
error e and repeatedly calculating a new approximate value x using: (x + n / x)
/ 2; we are finished when the previous x and the new x have an absolute
difference less than e.

We supply to a function (int_rac) a number n (positive integer) and a parameter
guess (positive integer) which will be our initial x. For this kata the
parameter 'e' is set to 1.

Hero's algorithm is not always going to come to an exactly correct result! For
instance: if n = 25 we get 5 but for n = 26 we also get 5. Nevertheless 5 is the
integer square root of 26.

The kata is to return the count of the progression of approximations that the
algorithm makes.

Reference:

https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method

Some examples:

int_rac(25,1): follows a progression of [1,13,7,5] so our function should return
4.

int_rac(125348,300): has a progression of [300,358,354] so our function should
return 3.

int_rac(125348981764,356243): has a progression of [356243,354053,354046] so our
function should return 3.
Note for JavaScript, Coffescript, Typescript

Don't use the double bitwise NOT ~~ at each iteration if you want to have the
same results as in the tests and the other languages. You can use Math.floor for
each integer approximation.
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
  static long long intRac_01(long long n, long long guess) {
    long long ret = 0;
    long long g_old = guess - 2;
    while (abs(guess - g_old) >= 1) {
      ++ret;
      g_old = guess;
      guess = (n / guess + guess) >> 1;
    }
    return ret;
  }

  static long long intRac_02(long long n, long long guess) {
    long long ret = 0;
    long long g_old = 0;
    do {
      ++ret;
      g_old = guess;
      guess = (n / guess + guess) >> 1;
    } while (abs(guess - g_old) >= 1);
    return ret;
  }
};

class TestCase {
 public:
  const long long n;
  const long long guess;
  const long long expected;
  TestCase(long long n_, long long guess_, long long expected_)
      : n(n_), guess(guess_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<long long(long long, long long)> &intRac) {
  vector<TestCase> testcases;
  uniform_int_distribution<long long> uni1(100000, 100000000);
  uniform_int_distribution<long long> uni2(1000, 1000000);
  for (int i = 0; i < 100; ++i) {
    long long n = uni1(gen);
    long long guess = uni2(gen);
    long long expected = intRac(n, guess);
    testcases.push_back(TestCase(n, guess, expected));
  }
  return testcases;
}

void test(const function<long long(long long, long long)> &intRac,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const long long actual = intRac(testcase.n, testcase.guess);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.n << " | " << testcase.guess << endl;
      cout << "\tout:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

unsigned long test_spd(const function<long long(long long, long long)> &intRac,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) intRac(testcase.n, testcase.guess);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.intRac_01);
  cout << "test..." << endl;
  cout << "intRac_01" << endl, test(sol.intRac_01, testcases);
  cout << "intRac_02" << endl, test(sol.intRac_02, testcases);
  cout << "test_spd..." << endl;
  cout << "intRac_01:\t" << test_spd(sol.intRac_01, testcases) << "ms" << endl;
  cout << "intRac_02:\t" << test_spd(sol.intRac_02, testcases) << "ms" << endl;
  return 0;
}