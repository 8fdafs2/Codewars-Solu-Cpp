/*
https://www.codewars.com/kata/56a32dd6e4f4748cc3000006

dataand data1 are two strings with rainfall records of a few cities for months
from January to December. The records of towns are separated by \n. The name of
each town is followed by :.

data and towns can be seen in "Your Test Cases:".

Task:

- function: mean(town, strng) should return the average of rainfall for the city
`town` and the `strng` `data` or `data1`.
- function: variance(town, strng) should return the variance of rainfall for the
city `town` and the `strng` `data` or `data1`.
Examples:

mean("London", data), 51.19(9999999999996)
variance("London", data), 57.42(833333333374)
Notes:

- if functions `mean`or `variance` have as parameter `town` a city which has no
records return `-1`
- Don't truncate or round: the tests will pass if `abs(your_result -
test_result) <= 1e-2`.
- <http://www.mathsisfun.com/data/standard-deviation.html>
- `data` and `data1` are adapted from <http://www.worldclimate.com>
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
  static vector<double> datget_01(const string &town, const string &strng) {
    size_t pos_s = strng.find(town + ':');
    vector<double> dat;
    if (pos_s == string::npos) return dat;
    pos_s += town.size() + 1;
    size_t pos_e = strng.find('\n', pos_s);
    if (pos_e == string::npos) pos_e = strng.size();
    size_t pos_d;
    while (1) {
      pos_d = strng.find(' ', pos_s + 1);
      pos_s = strng.find(',', pos_d + 1);
      if (pos_s > pos_e) {
        dat.push_back(stod(strng.substr(pos_d + 1, pos_e - pos_d - 1)));
        break;
      }
      dat.push_back(stod(strng.substr(pos_d + 1, pos_s - pos_d - 1)));
    }
    return dat;
  }
  static double mean_01(const string &town, const string &strng) {
    const vector<double> &dat = datget_01(town, strng);
    if (dat.empty()) return -1;
    size_t l = dat.size();
    double sum{0};
    for (size_t i = 0; i < l; ++i) sum += dat[i];
    return sum / l;
  }
  static double variance_01(const string &town, const string &strng) {
    const vector<double> &dat = datget_01(town, strng);
    if (dat.empty()) return -1;
    size_t l = dat.size();
    double sum{0};
    for (size_t i = 0; i < l; ++i) sum += dat[i];
    double mea = sum / l;
    sum = 0;
    for (size_t i = 0; i < l; ++i) sum += pow(dat[i] - mea, 2);
    return sum / l;
  }

  static vector<string> split_02(const string &s, char delim) {
    vector<string> out;
    istringstream ss(s);
    string next;
    while (getline(ss, next, delim)) out.push_back(next);
    return out;
  }
  static vector<double> datget_02(const string &town, const string &strng) {
    vector<string> towns = split_02(strng, '\n');
    vector<double> ret;
    size_t l = town.size() + 1;
    for (string &s : towns) {
      if (s.substr(0, l) == town + ':') {
        vector<string> months = split_02(s.substr(l + 1), ',');
        for (string &m : months) ret.push_back(stod(split_02(m, ' ').back()));
        break;
      }
    }
    return ret;
  }
  static double mean_02(const string &town, const string &strng) {
    const vector<double> &dat = datget_02(town, strng);
    if (dat.empty()) return -1;
    size_t l = dat.size();
    double sum{0};
    for (auto i : dat) sum += i;
    return sum / l;
  }

  static double variance_02(const string &town, const string &strng) {
    const vector<double> &dat = datget_02(town, strng);
    if (dat.empty()) return -1;
    size_t l = dat.size();
    double sum{0};
    for (auto i : dat) sum += i;
    double mea = sum / l;
    sum = 0;
    for (auto i : dat) sum += pow(i - mea, 2);
    return sum / l;
  }
};

class TestCase {
 public:
  const string town;
  const string strng;
  const double expected_01;
  const double expected_02;
  TestCase(const string &town_, const string &strng_, double expected_01_,
           double expected_02_)
      : town(town_),
        strng(strng_),
        expected_01(expected_01_),
        expected_02(expected_02_) {
    // Constructor
  }
};

vector<string> data_g{
    "Rome:Jan 81.2,Feb 63.2,Mar 70.3,Apr 55.7,May 53.0,Jun 36.4,Jul 17.5,Aug "
    "27.5,Sep 60.9,Oct 117.7,Nov 111.0,Dec 97.9\n"
    "London:Jan 48.0,Feb 38.9,Mar 39.9,Apr 42.2,May 47.3,Jun 52.1,Jul 59.5,Aug "
    "57.2,Sep 55.4,Oct 62.0,Nov 59.0,Dec 52.9\n"
    "Paris:Jan 182.3,Feb 120.6,Mar 158.1,Apr 204.9,May 323.1,Jun 300.5,Jul "
    "236.8,Aug 192.9,Sep 66.3,Oct 63.3,Nov 83.2,Dec 154.7\n"
    "NY:Jan 108.7,Feb 101.8,Mar 131.9,Apr 93.5,May 98.8,Jun 93.6,Jul 102.2,Aug "
    "131.8,Sep 92.0,Oct 82.3,Nov 107.8,Dec 94.2\n"
    "Vancouver:Jan 145.7,Feb 121.4,Mar 102.3,Apr 69.2,May 55.8,Jun 47.1,Jul "
    "31.3,Aug 37.0,Sep 59.6,Oct 116.3,Nov 154.6,Dec 171.5\n"
    "Sydney:Jan 103.4,Feb 111.0,Mar 131.3,Apr 129.7,May 123.0,Jun 129.2,Jul "
    "102.8,Aug 80.3,Sep 69.3,Oct 82.6,Nov 81.4,Dec 78.2\n"
    "Bangkok:Jan 10.6,Feb 28.2,Mar 30.7,Apr 71.8,May 189.4,Jun 151.7,Jul "
    "158.2,Aug 187.0,Sep 319.9,Oct 230.8,Nov 57.3,Dec 9.4\n"
    "Tokyo:Jan 49.9,Feb 71.5,Mar 106.4,Apr 129.2,May 144.0,Jun 176.0,Jul "
    "135.6,Aug 148.5,Sep 216.4,Oct 194.1,Nov 95.6,Dec 54.4\n"
    "Beijing:Jan 3.9,Feb 4.7,Mar 8.2,Apr 18.4,May 33.0,Jun 78.1,Jul 224.3,Aug "
    "170.0,Sep 58.4,Oct 18.0,Nov 9.3,Dec 2.7\n"
    "Lima:Jan 1.2,Feb 0.9,Mar 0.7,Apr 0.4,May 0.6,Jun 1.8,Jul 4.4,Aug 3.1,Sep "
    "3.3,Oct 1.7,Nov 0.5,Dec 0.7",
    "Rome:Jan 90.2,Feb 73.2,Mar 80.3,Apr 55.7,May 53.0,Jun 36.4,Jul 17.5,Aug "
    "27.5,Sep 60.9,Oct 147.7,Nov 121.0,Dec 97.9\n"
    "London:Jan 58.0,Feb 38.9,Mar 49.9,Apr 42.2,May 67.3,Jun 52.1,Jul 59.5,Aug "
    "77.2,Sep 55.4,Oct 62.0,Nov 69.0,Dec 52.9\n"
    "Paris:Jan 182.3,Feb 120.6,Mar 188.1,Apr 204.9,May 323.1,Jun 350.5,Jul "
    "336.8,Aug 192.9,Sep 66.3,Oct 63.3,Nov 83.2,Dec 154.7\n"
    "NY:Jan 128.7,Feb 121.8,Mar 151.9,Apr 93.5,May 98.8,Jun 93.6,Jul 142.2,Aug "
    "131.8,Sep 92.0,Oct 82.3,Nov 107.8,Dec 94.2\n"
    "Vancouver:Jan 155.7,Feb 121.4,Mar 132.3,Apr 69.2,May 85.8,Jun 47.1,Jul "
    "31.3,Aug 37.0,Sep 69.6,Oct 116.3,Nov 154.6,Dec 171.5\n"
    "Sydney:Jan 123.4,Feb 111.0,Mar 151.3,Apr 129.7,May 123.0,Jun 159.2,Jul "
    "102.8,Aug 90.3,Sep 69.3,Oct 82.6,Nov 81.4,Dec 78.2\n"
    "Bangkok:Jan 20.6,Feb 28.2,Mar 40.7,Apr 81.8,May 189.4,Jun 151.7,Jul "
    "198.2,Aug 197.0,Sep 319.9,Oct 230.8,Nov 57.3,Dec 9.4\n"
    "Tokyo:Jan 59.9,Feb 81.5,Mar 106.4,Apr 139.2,May 144.0,Jun 186.0,Jul "
    "155.6,Aug 148.5,Sep 216.4,Oct 194.1,Nov 95.6,Dec 54.4\n"
    "Beijing:Jan 13.9,Feb 14.7,Mar 18.2,Apr 18.4,May 43.0,Jun 88.1,Jul "
    "224.3,Aug 170.0,Sep 58.4,Oct 38.0,Nov 19.3,Dec 2.7\n"
    "Lima:Jan 11.2,Feb 10.9,Mar 10.7,Apr 10.4,May 10.6,Jun 11.8,Jul 14.4,Aug "
    "13.1,Sep 23.3,Oct 1.7,Nov 0.5,Dec 10.7"};
vector<string> towns_g = {
    "Rome",       "Rom",     "London", "Paris",  "NY",      "Vancouver",
    "Sydney",     "Bangkok", "Bangko", "Tokyo",  "Beijing", "Lima",
    "Montevideo", "Caracas", "Madrid", "Berlin", "Lon"};

const vector<TestCase> set_gen(
    const function<double(const string &, const string &)> &mean,
    const function<double(const string &, const string &)> &variance) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(0, 100);
  for (int i = 0; i < 100; ++i) {
    const string &town = choice(towns_g);
    const string &strng = choice(data_g);
    double expected_01 = mean(town, strng);
    double expected_02 = variance(town, strng);
    testcases.push_back(TestCase(town, strng, expected_01, expected_02));
  }
  return testcases;
}

void test(const function<double(const string &, const string &)> &mean,
          const function<double(const string &, const string &)> &variance,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const double actual_01 = mean(testcase.town, testcase.strng);
    try {
      Assert<Wrong>(abs(actual_01 - testcase.expected_01) < 0.00001);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.town << " | " << testcase.strng << endl;
      cout << "\tout:" << actual_01 << " vs. " << testcase.expected_01 << endl;
    }
    const double actual_02 = variance(testcase.town, testcase.strng);
    try {
      Assert<Wrong>(abs(actual_02 - testcase.expected_02) < 0.00001);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.town << " | " << testcase.strng << endl;
      cout << "\tout:" << actual_02 << " vs. " << testcase.expected_02 << endl;
    }
  }
}

unsigned long test_spd(
    const function<double(const string &, const string &)> &mean,
    const function<double(const string &, const string &)> &variance,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) {
      mean(testcase.town, testcase.strng);
      variance(testcase.town, testcase.strng);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.mean_01, sol.variance_01);
  cout << "test..." << endl;
  cout << "mean_01 | variance_01" << endl,
      test(sol.mean_01, sol.variance_01, testcases);
  cout << "mean_02 | variance_02" << endl,
      test(sol.mean_02, sol.variance_02, testcases);
  cout << "test_spd..." << endl;
  cout << "mean_01 | variance_01:\t"
       << test_spd(sol.mean_01, sol.variance_01, testcases) << "ms" << endl;
  cout << "mean_02 | variance_02:\t"
       << test_spd(sol.mean_02, sol.variance_02, testcases) << "ms" << endl;
  return 0;
}