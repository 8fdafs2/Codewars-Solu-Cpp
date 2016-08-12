/*
https://www.codewars.com/kata/sum-without-highest-and-lowest-number

Sum all the numbers of the array except the highest and the lowest element.
(Only one element at each edge, even if there are more than one with the same
value!)

Example: { 6, 2, 1, 8, 10 } => 16

If array is empty or null, or if only 1 Element exists, return 0.
Note: in C++ instead null an empty vector is used.

Have fun coding it and please don't forget to vote and rank this kata! :-)

I have created other katas. Have a look if you like coding and challenges.
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static int sum_01(vector<int> numbers) {
    if (numbers.size() < 2) return 0;
    int min{numeric_limits<int>::max()};
    int max{numeric_limits<int>::min()};
    int ret{0};
    for (int i = 0; i < numbers.size(); i++) {
      int num = numbers[i];
      if (num > max) max = num;
      if (num < min) min = num;
      ret += num;
    }
    return ret - min - max;
  };
  static int sum_02(vector<int> numbers) {
    if (numbers.size() < 2) return 0;
    auto b{numbers.begin()};
    auto e{numbers.end()};
    return accumulate(b, e, 0) - *max_element(b, e) - *min_element(b, e);
  };
  static int sum_03(vector<int> numbers) {
    if (numbers.size() < 2) return 0;
    int ret = 0;
    vector<int> nums = numbers;
    sort(nums.begin(), nums.end());
    nums.pop_back();
    // nums.erase(nums.begin());
    for (int n : nums) ret += n;
    return ret - nums.front();
  };
  static int sum_04(vector<int> numbers) {
    if (numbers.size() < 2) return 0;
    numbers.erase(min_element(numbers.begin(), numbers.end()));
    numbers.erase(max_element(numbers.begin(), numbers.end()));
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++) sum += numbers[i];
    return sum;
  };
};

class TestCase {
 public:
  vector<int> numbers;
  int expected;
  TestCase(const vector<int> &numbers_, const int expected_)
      : numbers(numbers_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<int(vector<int>)> &sum) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    vector<int> numbers;
    int l = rand() % 100;
    for (int j = 0; j < l; j++) {
      numbers.push_back(rand() % 100);
    }
    int expected = sum(numbers);
    testcases.push_back(TestCase(numbers, expected));
  }
  return testcases;
}

void test(const function<int(vector<int>)> &sum,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(sum(testcase.numbers) == testcase.expected);
  }
}

unsigned long test_spd(const function<int(vector<int>)> &sum,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) sum(testcase.numbers);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<microseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.sum_01);
  test(sol.sum_01, testcases);
  test(sol.sum_02, testcases);
  test(sol.sum_03, testcases);
  test(sol.sum_04, testcases);
  cout << "sum_01:\t" << test_spd(sol.sum_01, testcases) << "ms" << endl;
  cout << "sum_02:\t" << test_spd(sol.sum_02, testcases) << "ms" << endl;
  cout << "sum_03:\t" << test_spd(sol.sum_03, testcases) << "ms" << endl;
  cout << "sum_04:\t" << test_spd(sol.sum_04, testcases) << "ms" << endl;
  return 0;
}