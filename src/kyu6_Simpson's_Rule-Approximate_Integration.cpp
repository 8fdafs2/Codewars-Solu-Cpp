/*
https://www.codewars.com/kata/simpsons-rule-approximate-integration

An integral:

\int_{a}^{b}f(x)dx

can be approximated by the so-called Simpson’s rule:

 \frac{b-a}{3n}(f(a)+f(b)+4\sum_{i=1}^{n/2}f(a+(2i-1)h)+2\sum_{i=1}^{n/2-1}f(a+2ih))

Here h = (b-a)/n, n being an even integer and a <= b. We want to try Simpson's
rule with the function f:

f(x) = \frac{3}{2}sin^3x

The task is to write a function called simpson with parameter n which returns
the value of the integral of f on the interval \left [ \right 0,\pi\left \right
] . The tests will pass if abs(your_result - test_result) <= 1e-10). n will
always be even.

Note: we know that the exact value of the integral of f on the given interval is
2.

You can see:
http://www.codewars.com/kata/5562ab5d6dca8009f7000050/train/javascript about
rectangle method and trapezoidal rule.
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
  static double f(double x) { return 3.0 / 2 * pow(sin(x), 3); };
  static double simpson_01(int n) {
    double ret = 0;
    double x_lst[n + 1];
    double w = M_PI;
    double h = w / n;
    for (int i = 0; i < n + 1; i++) x_lst[i] = h * i;
    for (int i = 1; i < n; i++)
      ret += i % 2 == 1 ? 4 * f(x_lst[i]) : 2 * f(x_lst[i]);
    return (ret + f(x_lst[0]) + f(x_lst[n])) * h / 3;
  };

  static double simpson_02(int n) {
    int N = n / 2;
    int i = 1;
    double d_sum_1 = 0.0;
    double d_sum_2 = 0.0;
    for (; i <= N - 1; i++) {
      d_sum_1 += pow(sin(M_PI * (2 * i - 1) / n), 3);
      d_sum_2 += pow(sin(M_PI * (2 * i) / n), 3);
    }
    d_sum_1 += pow(sin(M_PI * (2 * i - 1) / n), 3);
    return M_PI / n * (2.0 * d_sum_1 + d_sum_2);
  };

  static double simpson_03(int n) {
    double h = M_PI / n;
    double s1 = 0;
    for (int i = 1; i <= n / 2; i++) s1 += f((2 * i - 1) * h);
    double s2 = 0;
    for (int i = 1; i <= n / 2 - 1; i++) s2 += f(2 * i * h);
    return M_PI / (3 * n) * (f(0) + f(M_PI) + 4 * s1 + 2 * s2);
  };
};

class TestCase {
 public:
  int n;
  double expected;
  TestCase(int n_, double expected_) : n(n_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<double(int)> &simpson) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int n = 2; n < 201; n += 2) {
    double expected = simpson(n);
    testcases.push_back(TestCase(n, expected));
  }
  return testcases;
}

void test(const function<double(int)> &simpson,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(abs(simpson(testcase.n) - testcase.expected) < 1e-10);
  }
}

unsigned long test_spd(const function<double(int)> &simpson,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) simpson(testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.simpson_01);
  test(sol.simpson_01, testcases);
  test(sol.simpson_02, testcases);
  test(sol.simpson_03, testcases);
  cout << "simpson_01:\t" << test_spd(sol.simpson_01, testcases) << "ms"
       << endl;
  cout << "simpson_02:\t" << test_spd(sol.simpson_02, testcases) << "ms"
       << endl;
  cout << "simpson_03:\t" << test_spd(sol.simpson_03, testcases) << "ms"
       << endl;
  return 0;
}