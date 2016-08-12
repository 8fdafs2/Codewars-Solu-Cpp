/*
https://www.codewars.com/kata/are-the-numbers-in-order

Are the numbers in order?

In this Kata, your function receives an array of positive integers as input.
Your task is to determine whether the numbers are in ascending order.

For the purposes of this Kata, you may assume that all inputs are valid (i.e.
arrays containing only positive integers with a length of at least 2).

For example:

Extra Challenge: If time, try to optimise and shorten your code as much as
possible.
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static bool isAscOrder_01(vector<int> arr) {
    int x = numeric_limits<int>::min();
    for (int a : arr) {
      if (a < x) return false;
      x = a;
    }
    return true;
  }

  static bool isAscOrder_02(vector<int> arr) {
    for (int i = 1; i < arr.size(); i++) {
      if (arr[i] < arr[i - 1]) {
        return false;
      }
    }
    return true;
  }

  static bool isAscOrder_03(vector<int> arr) {
    adjacent_difference(arr.begin(), arr.end(), arr.begin());
    return any_of(arr.begin(), arr.end(), [](int i) { return i < 0; }) ? false
                                                                       : true;
  }

  static bool isAscOrder_04(vector<int> arr) {
    vector<int> tmp = arr;
    sort(tmp.begin(), tmp.end());
    return tmp == arr ? 1 : 0;
  }

  static bool isAscOrder_05(vector<int> arr) {
    return is_sorted(begin(arr), end(arr));
  }
};

class TestCase {
 public:
  vector<int> arr;
  bool expected;
  TestCase(const vector<int> &arr_, const bool expected_)
      : arr(arr_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<bool(vector<int>)> &isAscOrder) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    vector<int> arr;
    int l = rand() % 101 + 2;
    for (int j = 0; j < l; j++) {
      arr.push_back(rand() % 101);
    }
    bool expected = isAscOrder(arr);
    testcases.push_back(TestCase(arr, expected));
  }
  return testcases;
}

void test(const function<bool(vector<int>)> &isAscOrder,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(isAscOrder(testcase.arr) == testcase.expected);
  }
}

unsigned long test_spd(const function<bool(vector<int>)> &isAscOrder,
                       const vector<TestCase> &testcases,
                       unsigned int ntimes = 1000) {
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = ntimes;
    chrono::high_resolution_clock::time_point t1 =
        chrono::high_resolution_clock::now();
    while (n--) isAscOrder(testcase.arr);
    chrono::high_resolution_clock::time_point t2 =
        chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.isAscOrder_01);
  test(sol.isAscOrder_01, testcases);
  test(sol.isAscOrder_02, testcases);
  test(sol.isAscOrder_03, testcases);
  test(sol.isAscOrder_04, testcases);
  test(sol.isAscOrder_05, testcases);
  cout << "isAscOrder_01:\t" << test_spd(sol.isAscOrder_01, testcases) << "ms"
       << endl;
  cout << "isAscOrder_02:\t" << test_spd(sol.isAscOrder_02, testcases) << "ms"
       << endl;
  cout << "isAscOrder_03:\t" << test_spd(sol.isAscOrder_03, testcases) << "ms"
       << endl;
  cout << "isAscOrder_04:\t" << test_spd(sol.isAscOrder_04, testcases) << "ms"
       << endl;
  cout << "isAscOrder_05:\t" << test_spd(sol.isAscOrder_05, testcases) << "ms"
       << endl;
  return 0;
}