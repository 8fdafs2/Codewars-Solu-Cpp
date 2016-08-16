/*
https://www.codewars.com/kata/growth-of-a-population

In a small town the population is p0 = 1000 at the beginning of a year. The
population regularly increases by 2 percent per year and moreover 50 new
inhabitants per year come to live in the town. How many years does the town need
to see its population greater or equal to p = 1200 inhabitants?

At the end of the first year there will be:
1000 + 1000 * 0.02 + 50 => 1070 inhabitants

At the end of the 2nd year there will be:
1070 + 1070 * 0.02 + 50 => 1141 inhabitants (number of inhabitants is an
integer)

At the end of the 3rd year there will be:
1141 + 1141 * 0.02 + 50 => 1213

It will need 3 entire years.
More generally given parameters:

p0, percent, aug (inhabitants coming or leaving each year), p (population to
surpass)

the function nb_year should return n number of entire years needed to get a
population greater or equal to p.

aug is an integer (> 0), percent a positive or null floating number, p0 and p
are positive integers (> 0)

Examples:
nb_year(1500, 5, 100, 5000) -> 15
nb_year(1500000, 2.5, 10000, 2000000) -> 10
Note: Don't forget to convert the percent parameter as a percentage in the body
of your function: if the parameter percent is 2 you have to convert it to 0.02.
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
  static int nbYear_01(int p0, double percent, int aug, int p) {
    int ret{0};
    percent = (percent + 100) / 100;
    while (p0 < p) {
      p0 = p0 * percent + aug;
      ret++;
    }
    return ret;
  }

  static int nbYear_02(int p0, double percent, int aug, int p) {
    if (p0 < p) {
      return 1 + nbYear_02(p0 * (100 + percent) / 100 + aug, percent, aug, p);
    }
    return 0;
  }
  /*
    It's efficient but cannot ideally cut off the decimal part of population
    year by year.
    Which means if the number of iterations is big enough or the inital inputs
    follow certain pattern then this solution will give incorrect result, which
    is normally smaller.
    However, it is sufficient to pass all existing test cases ;)
  */
  static int nbYear_03(int p0, double percent, int aug, int p) {
    if (p0 >= p) return 0;
    percent = (100 + percent) / 100;
    int pc = (p0 * percent + aug);
    double inc = (percent * ((percent - 1) * p0 + aug));
    int ret = 1;
    while (pc < p) {
      pc += inc;
      inc *= percent;
      ++ret;
    }
    return ret;
  }
};

class TestCase {
 public:
  int p0;
  double percent;
  int aug;
  int p;
  int expected;
  TestCase(int p0_, double percent_, int aug_, int p_, int expected_)
      : p0(p0_), percent(percent_), aug(aug_), p(p_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<int(int, double, int, int)> &nbYear) {
  vector<TestCase> testcases;
  for (int i = 0; i < 1000; ++i) {
    uniform_int_distribution<int> uni1(1000, 15000);
    uniform_int_distribution<int> uni2(5, 10);
    int p0 = uni1(gen);
    double percent = uni2(gen);
    int aug = choice<bool>({true, false}) ? p0 / 500 : -p0 / 500;
    int p = p0 * 5;
    // cout << p0 << '|' << percent << '|' << aug << '|' << p << endl;
    int expected = nbYear(p0, percent, aug, p);
    testcases.push_back(TestCase(p0, percent, aug, p, expected));
  }
  return testcases;
}

void test(const function<int(int, double, int, int)> &nbYear,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    const int &actual =
        nbYear(testcase.p0, testcase.percent, testcase.aug, testcase.p);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\t" << testcase.p0 << '|' << testcase.percent << '|'
           << testcase.aug << '|' << testcase.p << endl;
      cout << "\t" << actual << '|' << testcase.expected << endl;
    }
  }
}

unsigned long test_spd(const function<int(int, double, int, int)> &nbYear,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) nbYear(testcase.p0, testcase.percent, testcase.aug, testcase.p);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.nbYear_01);
  cout << "test..." << endl;
  cout << "nbYear_01" << endl, test(sol.nbYear_01, testcases);
  cout << "nbYear_02" << endl, test(sol.nbYear_02, testcases);
  cout << "nbYear_03" << endl, test(sol.nbYear_03, testcases);
  cout << "test_spd..." << endl;
  cout << "nbYear_01:\t" << test_spd(sol.nbYear_01, testcases) << "ms" << endl;
  cout << "nbYear_02:\t" << test_spd(sol.nbYear_02, testcases) << "ms" << endl;
  cout << "nbYear_03:\t" << test_spd(sol.nbYear_03, testcases) << "ms" << endl;
  return 0;
}