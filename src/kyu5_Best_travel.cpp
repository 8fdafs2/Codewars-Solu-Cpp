/*
https://www.codewars.com/kata/best-travel

John and Mary want to travel between a few towns A, B, C ... Mary has on a sheet
of paper a list of distances between these towns. ls = [50, 55, 57, 58, 60].
John is tired of driving and he says to Mary that he doesn't want to drive more
than t = 174 miles and he will visit only 3 towns.

Which distances, hence which towns, they will choose so that the sum of the
distances is the biggest possible - to please Mary - but less than t - to please
John- ?

Example:

With list ls and 3 towns to visit they can make a choice between:
[50,55,57],[50,55,58],[50,55,60],[50,57,58],[50,57,60],[50,58,60],[55,57,58],[55,57,60],[55,58,60],[57,58,60].

The sums of distances are then: 162, 163, 165, 165, 167, 168, 170, 172, 173,
175.

The biggest possible sum taking a limit of 174 into account is then 173 and the
distances of the 3 corresponding towns is [55, 58, 60].

The function chooseBestSum (or choose_best_sum or ... depending on the language)
will take as parameters t (maximum sum of distances, integer >= 0), k (number of
towns to visit, k >= 1) and ls (list of distances, all distances are positive or
null integers and this list has at least one element). The function returns the
"best" sum ie the biggest possible sum of k distances less than or equal to the
given limit t, if that sum exists, or otherwise nil, null, None, Nothing,
depending on the language. With C++ return -1.

Examples:

ts = [50, 55, 56, 57, 58] choose_best_sum(163, 3, ts) -> 163

xs = [50] choose_best_sum(163, 3, xs) -> nil (or null or ... or -1 (C++)

ys = [91, 74, 73, 85, 73, 81, 87] choose_best_sum(230, 3, ys) -> 228
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
  static int chooseBestSum_01(int t, int k, const vector<int> &ls) {
    int n = ls.size();
    if (n < k) return -1;
    int ret{-1};
    string bitmask(k, 1);
    bitmask.resize(n, 0);
    do {
      int sum{0};
      for (int i = 0; i < n; ++i)
        if (bitmask[i]) sum += ls[i];
      if (sum <= t && sum > ret) ret = sum;
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
    return ret;
  };
};

class TestCase {
 public:
  int t;
  int k;
  vector<int> ls;
  int expected;
  TestCase(int t_, int k_, const vector<int> &ls_, int expected_)
      : t(t_), k(k_), ls(ls_), expected(expected_) {
    // Constructor
  }
};

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

vector<int> doEx() {
  vector<int> result;
  uniform_int_distribution<int> uni1(4, 8);
  uniform_int_distribution<int> uni2(20, 60);
  int k = uni1(gen);
  for (int i = 0; i < k; ++i) {
    int rnd = uni2(gen);
    result.push_back(rnd);
  }
  return result;
}

const vector<TestCase> set_gen(
    const function<int(int, int, const vector<int> &)> &chooseBestSum) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(50, 500);
  uniform_int_distribution<int> uni2(2, 6);
  for (int i = 0; i < 10; i++) {
    const vector<int> &ls = doEx();
    int t = uni1(gen);
    int k = uni2(gen);
    int expected = chooseBestSum(t, k, ls);
    testcases.push_back(TestCase(t, k, ls, expected));
  }
  return testcases;
}

void test(const function<int(int, int, const vector<int> &)> &chooseBestSum,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(chooseBestSum(testcase.t, testcase.k, testcase.ls) ==
           testcase.expected);
  }
}

unsigned long test_spd(
    const function<int(int, int, const vector<int> &)> &chooseBestSum,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) chooseBestSum(testcase.t, testcase.k, testcase.ls);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.chooseBestSum_01);
  test(sol.chooseBestSum_01, testcases);
  cout << "chooseBestSum_01:\t" << test_spd(sol.chooseBestSum_01, testcases)
       << "ms" << endl;
  return 0;
}
