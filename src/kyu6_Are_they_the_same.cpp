/*
https://www.codewars.com/kata/are-they-the-same

Given two arrays a and b write a function comp(a, b) (compSame(a, b) in Clojure)
that checks whether the two arrays have the "same" elements, with the same
multiplicities. "Same" means, here, that the elements in b are the elements in a
squared, regardless of the order.

Examples

Valid arrays

a = [121, 144, 19, 161, 19, 144, 19, 11]
b = [121, 14641, 20736, 361, 25921, 361, 20736, 361]
comp(a, b) returns true because in b 121 is the square of 11, 14641 is the
square of 121, 20736 the square of 144, 361 the square of 19, 25921 the square
of 161, and so on. It gets obvious if we write b's elements in terms of squares:

a = [121, 144, 19, 161, 19, 144, 19, 11]
b = [11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19]
Invalid arrays

If we change the first number to something else, comp may not return true
anymore:

a = [121, 144, 19, 161, 19, 144, 19, 11]
b = [132, 14641, 20736, 361, 25921, 361, 20736, 361]
comp(a,b) returns false because in b 132 is not the square of any number of a.

a = [121, 144, 19, 161, 19, 144, 19, 11]
b = [121, 14641, 20736, 36100, 25921, 361, 20736, 361]
comp(a,b) returns false because in b 36100 is not the square of any number of a.

Remarks

a or b might be [] (all languages). a or b might be nil or null or None (except
in Haskell, Elixir, C++).

If a or b are nil (or null or None), the problem doesn't make sense so return
false.

If a or b are empty the result is evident by itself.
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
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
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  static bool comp_01(vector<int> a, vector<int> b) {
    for (int i = 0; i < a.size(); i++) a[i] *= a[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
  };
  static bool comp_02(vector<int> a, vector<int> b) {
    unordered_set<int> st;
    for (int i = 0; i < a.size(); i++) st.insert(a[i] * a[i]);
    for (int i = 0; i < b.size(); i++)
      if (st.find(b[i]) == st.end()) return false;
    return true;
  };
};

class TestCase {
 public:
  vector<int> a;
  vector<int> b;
  bool expected;
  TestCase(const vector<int> &a_, const vector<int> &b_, bool expected_)
      : a(a_), b(b_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(
    const function<bool(vector<int>, vector<int>)> &comp) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int l = rand() % 10 + 10;
    vector<int> a(l);
    vector<int> b(l);
    for (int j = 0; j < l; j++) a[j] = rand() % 100;
    if (rand() % 2) {
      for (int j = 0; j < l; j++) b[j] = rand() % 100;
    } else {
      for (int j = 0; j < l; j++) b[j] = a[j] * a[j];
    }
    bool expected = comp(a, b);
    testcases.push_back(TestCase(a, b, expected));
  }
  return testcases;
}

void test(const function<bool(vector<int>, vector<int>)> &comp,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(comp(testcase.a, testcase.b) == testcase.expected);
  }
}

unsigned long test_spd(const function<bool(vector<int>, vector<int>)> &comp,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) comp(testcase.a, testcase.b);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.comp_01);
  test(sol.comp_01, testcases);
  test(sol.comp_02, testcases);
  cout << "comp_01:\t" << test_spd(sol.comp_01, testcases) << "ms" << endl;
  cout << "comp_02:\t" << test_spd(sol.comp_02, testcases) << "ms" << endl;
  return 0;
}