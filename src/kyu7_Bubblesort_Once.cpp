/*
https://www.codewars.com/kata/bubblesort-once

Overview

The Bubblesort Algorithm is one of many algorithms used to sort a list of
similar items (e.g. all numbers or all letters) into either ascending order or
descending order.

Given a list (e.g.): 9, 7, 5, 3, 1, 2, 4, 6, 8
To sort this list in ascending order using Bubblesort, you first have to compare
the first two terms of the list. If the first term is larger than the second
term, you perform a swap. The list then becomes: 7, 9, 5, 3, 1, 2, 4, 6, 8. (the
"9" and "7" have been swapped because 9 is larger than 7 and thus 9 should be
after 7)

You then proceed by comparing the 2nd and 3rd terms, performing a swap when
necessary, and then the 3rd and 4th term, then the 4th and 5th term, etc. When
you reach the end of the list, it is said that you have completed 1 complete
pass.

Task

Program an algorithm in your selected language that performs exactly 1 complete
pass (no more, no less :D) of the Bubblesort algorithm to a list of positive
integers. You may assume all arguments provided are arrays containing at least 2
positive integers.
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static vector<int> bubbleSortOnce_01(vector<int> input) {
    vector<int> output = input;
    for (int i = 1; i < output.size(); ++i) {
      if (output[i - 1] > output[i]) {
        int t = output[i - 1];
        output[i - 1] = output[i];
        output[i] = t;
      }
    }
    return output;
  }
  static vector<int> bubbleSortOnce_02(vector<int> input) {
    vector<int> output = input;
    for (auto it = output.begin(); it < output.end() - 1; ++it) {
      if (*it > *(it + 1)) {
        swap(*it, *(it + 1));
      }
    }
    return output;
  }
  static vector<int> bubbleSortOnce_03(vector<int> input) {
    vector<int> output = input;
    for (auto i = output.begin(); i < output.end() - 1; ++i) {
      if ((*i) > *(i + 1)) {
        iter_swap(i, i + 1);
      }
    }
    return output;
  }
};

class TestCase {
 public:
  vector<int> input;
  vector<int> expected;
  TestCase(const vector<int> &input_, const vector<int> &expected_)
      : input(input_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<vector<int>(vector<int>)> &bubbleSortOnce) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int l = rand() % 101 + 2;
    vector<int> input;
    for (int j = 0; j < l; j++) {
      input.push_back(rand() % 101);
    }
    const vector<int> &expected = bubbleSortOnce(input);
    testcases.push_back(TestCase(input, expected));
  }
  return testcases;
}

void test(const function<vector<int>(vector<int>)> &bubbleSortOnce,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(bubbleSortOnce(testcase.input) == testcase.expected);
  }
}

unsigned long test_spd(const function<vector<int>(vector<int>)> &bubbleSortOnce,
                       const vector<TestCase> &testcases,
                       unsigned int ntimes = 1000) {
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = ntimes;
    chrono::high_resolution_clock::time_point t1 =
        chrono::high_resolution_clock::now();
    while (n--) bubbleSortOnce(testcase.input);
    chrono::high_resolution_clock::time_point t2 =
        chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.bubbleSortOnce_01);
  test(sol.bubbleSortOnce_01, testcases);
  test(sol.bubbleSortOnce_02, testcases);
  test(sol.bubbleSortOnce_03, testcases);
  cout << "bubbleSortOnce_01:\t" << test_spd(sol.bubbleSortOnce_01, testcases)
       << "ms" << endl;
  cout << "bubbleSortOnce_02:\t" << test_spd(sol.bubbleSortOnce_02, testcases)
       << "ms" << endl;
  cout << "bubbleSortOnce_03:\t" << test_spd(sol.bubbleSortOnce_03, testcases)
       << "ms" << endl;
  return 0;
}