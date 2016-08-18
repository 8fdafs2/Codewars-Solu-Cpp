/*
https://www.codewars.com/kata/integers-recreation-two

We are still with squared integers.

Given 4 integers a, b, c, d (positive or negative) we form the sum of the
squares of a and b and then the sum of the squares of c and d. We multiply the
two sums hence a number n and we try to decompose n in a sum of two squares e
and f (e and f positive integers) so that n = e² + f².

More: e and f must result only from sums (or differences) of products between on
the one hand (a, b) and on the other (c, d) each of a, b, c, d taken only once.

Suppose we have a = 1, b = 2, c = 1, d = 3. First we calculate the sums 1² + 2²
= 5 and 1² + 3² = 10 hence n = 50.

50 = 1² + 7² or 50 = 7² + 1² (we'll consider that these two solutions are the
same) or 50 = 5² + 5².

The return of our function will be an array of subarrays sorted on the first
elements of the subarrays. In each subarray the lower element should be the
first.

prod2sum(1, 2, 1, 3) should return [[1, 7], [5, 5]]

prod2sum(2, 3, 4, 5) should return [[2, 23], [7, 22]]

because (2² + 3²) * (4² + 5²) = 533 = (7² + 22²) = (23² + 2²)

prod2sum(1, 2, 2, 3) should return [[1, 8], [4, 7]]

prod2sum(1, 1, 3, 5) should return [[2, 8]] (there are not always 2 solutions).

Hint

Take a sheet of paper and with a bit of algebra try to write the product of
squared numbers in another way.
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
  static vector<pair<long, long>> prod2Sum_01(long a, long b, long c, long d) {
    vector<long> prods{a * c, a * d, b * c, b * d};
    vector<long> cands;
    for (int i = 0; i < 4; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        long sum = abs(prods[i] + prods[j]);
        long dif = abs(prods[i] - prods[j]);
        if (find(cands.begin(), cands.end(), sum) == cands.end())
          cands.push_back(sum);
        if (find(cands.begin(), cands.end(), dif) == cands.end())
          cands.push_back(dif);
      }
    }
    sort(cands.begin(), cands.end());
    long s = (a * a + b * b) * (c * c + d * d);
    long m = floor(sqrt(s >> 1));
    vector<pair<long, long>> ret;
    for (auto i : cands) {
      if (i > m) break;
      double j = sqrt(s - i * i);
      if (j == floor(j) &&
          find(cands.begin(), cands.end(), floor(j)) != cands.end())
        ret.push_back({i, j});
    }
    return ret;
  }

  static vector<pair<long, long>> prod2Sum_02(long a, long b, long c, long d) {
    long ac{a * c}, bd{b * d}, ad{a * d}, bc{b * c};
    long e1 = abs(ac + bd);
    long f1 = abs(ad - bc);
    long e2 = abs(ac - bd);
    long f2 = abs(ad + bc);
    if (e1 > f1) swap(e1, f1);
    if (e2 > f2) swap(e2, f2);
    if (e1 == e2) return {{e1, f1}};
    if (e1 < e2) return {{e1, f1}, {e2, f2}};
    return {{e2, f2}, {e1, f1}};
  }
};

class TestCase {
 public:
  long a;
  long b;
  long c;
  long d;
  vector<pair<long, long>> expected;
  TestCase(long a_, long b_, long c_, long d_,
           const vector<pair<long, long>> &expected_)
      : a(a_), b(b_), c(c_), d(d_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<vector<pair<long, long>>(long, long, long, long)>
        &prod2Sum) {
  vector<TestCase> testcases;
  uniform_int_distribution<long> uni1(1, 100);
  for (int i = 0; i < 100; ++i) {
    long a = uni1(gen);
    long b = uni1(gen);
    long c = uni1(gen);
    long d = uni1(gen);
    vector<pair<long, long>> expected = prod2Sum(a, b, c, d);
    testcases.push_back(TestCase(a, b, c, d, expected));
  }
  return testcases;
}

void test(
    const function<vector<pair<long, long>>(long, long, long, long)> &prod2Sum,
    const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const vector<pair<long, long>> &actual =
        prod2Sum(testcase.a, testcase.b, testcase.c, testcase.d);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "\t!!Assertion Failed!!" << endl;
      cout << "\tin: " << testcase.a << "|" << testcase.b << "|" << testcase.c
           << "|" << testcase.d << endl;
      cout << "\tout:\n\t\t";
      for (auto i : actual) cout << i.first << "-" << i.second << " ";
      cout << endl;
      cout << "\t\t vs.\n\t\t";
      for (auto i : testcase.expected)
        cout << i.first << "-" << i.second << " ";
      cout << endl;
    }
  }
}

unsigned long test_spd(
    const function<vector<pair<long, long>>(long, long, long, long)> &prod2Sum,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) prod2Sum(testcase.a, testcase.b, testcase.c, testcase.d);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.prod2Sum_01);
  cout << "test..." << endl;
  cout << "prod2Sum_01" << endl, test(sol.prod2Sum_01, testcases);
  cout << "prod2Sum_02" << endl, test(sol.prod2Sum_02, testcases);
  cout << "test_spd..." << endl;
  cout << "prod2Sum_01:\t" << test_spd(sol.prod2Sum_01, testcases) << "ms"
       << endl;
  cout << "prod2Sum_02:\t" << test_spd(sol.prod2Sum_02, testcases) << "ms"
       << endl;
  return 0;
}