/*
https://www.codewars.com/kata/pi-approximation

The aim of the kata is to try to show how difficult it can be to calculate
decimals of an irrational number with a certain precision. We have chosen to get
a few decimals of the number "pi" using

the following infinite series (Leibniz 1646–1716):

PI / 4 = 1 - 1/3 + 1/5 - 1/7 + ... which gives an approximation of PI / 4.

http://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80

To have a measure of the difficulty we will count how many iterations are needed
to calculate PI with a given precision.

There are several ways to determine the precision of the calculus but to keep
things easy we will calculate to within epsilon of your language Math::PI
constant. In other words we will stop the iterative process when the absolute
value of the difference between our calculation and the Math::PI constant is
less than epsilon.

Your function

iterPi(epsilon) must return a string :
"[numberOfIterations, approximationOfPi]"
where approximation of PI has 10 decimals

In Haskell you can use the function "trunc10Dble" (see "Your solution") and in
Clojure you can use the function "round" (see "Your solution") in order to avoid
discusssions about the result.

Examples :

your function calculates 1000 iterations and 3.140592653839794 but returns:
iterPi2String(0.001) --> "[1000, 3.1405926538]"
Unfortunately, this series converges too slowly to be useful, as it takes over
300 terms to obtain a 2 decimal place precision. To obtain 100 decimal places of
PI, it was calculated that one would need to use at least 10^50 terms of this
expansion!

About PI : http://www.geom.uiuc.edu/~huberty/math5337/groupe/expresspi.html
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

#define M_PI 3.14159265358979323846 /* pi */

class Solution {
 public:
  static string iterPi_01(double epsilon) {
    ostringstream ss;
    double pi = 0;
    int n = 1;
    double sign = 1.0;
    while (fabs(M_PI - 4 * pi) >= epsilon) {
      pi += sign / n;
      n += 2;
      sign = -sign;
    }
    ss << "[" << (n - 1) / 2 << ", " << setprecision(11) << 4 * pi << "]";
    return ss.str();
  };

  static string iterPi_02(double epsilon) {
    double pi = 1.0;
    int iter = 1;
    while (fabs(M_PI - 4 * pi) > epsilon)
      pi += (iter % 2 == 0 ? 1.0 : -1.0) / (1 + 2 * iter++);
    ostringstream oss;
    oss << "[" << iter << ", " << std::setprecision(11) << 4 * pi << "]";
    return oss.str();
  };
};

class TestCase {
 public:
  double epsilon;
  string expected;
  TestCase(double epsilon_, const string &expected_)
      : epsilon(epsilon_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(double)> &iterPi) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 1; i < 1000; i++) {
    double epsilon = 1.0 / i;
    string expected = iterPi(epsilon);
    testcases.push_back(TestCase(epsilon, expected));
  }
  return testcases;
}

void test(const function<string(double)> &iterPi,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(iterPi(testcase.epsilon) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(double)> &iterPi,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) iterPi(testcase.epsilon);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.iterPi_01);
  test(sol.iterPi_01, testcases);
  test(sol.iterPi_02, testcases);
  cout << "iterPi_01:\t" << test_spd(sol.iterPi_01, testcases) << "ms" << endl;
  cout << "iterPi_02:\t" << test_spd(sol.iterPi_02, testcases) << "ms" << endl;
  return 0;
}