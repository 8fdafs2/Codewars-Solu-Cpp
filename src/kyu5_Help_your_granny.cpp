/*
https://www.codewars.com/kata/help-your-granny

Your granny, who lives in town X0, has friends. These friends are given in an
array, for example: array of friends is

[ "A1", "A2", "A3", "A4", "A5" ].
The order of friends is this array must not be changed since this order gives
the order in which they will be visited.

These friends inhabit towns and you have an array with friends and towns, for
example:

[ ["A1", "X1"], ["A2", "X2"], ["A3", "X3"], ["A4", "X4"] ],
which means A1 is in town X1, A2 in town X2... It can happen that we don't know
the town of one of the friends.

Your granny wants to visit her friends and to know how many miles she will have
to travel.

You will make the circuit that permits her to visit her friends. For example
here the circuit will contain:

X0, X1, X2, X3, X4, X0
and you must compute the total distance

X0X1 + X1X2 + .. + X4X0.
For the distance, fortunately, you have a map (and a hashmap) that gives each
distance X0X1, X0X2 and so on. For example:

[ ["X1", 100.0], ["X2", 200.0], ["X3", 250.0], ["X4", 300.0] ]
which means that X1 is at 100.0 miles from X0, X2 at 200.0 miles from X0, etc...

More fortunately (it's not real life, it's a story...), the towns X0, X1, ..Xn
are placed in the following manner:

X0X1X2 is a right triangle with the right angle in X1, X0X2X3 is a right
triangle with the right angle in X2, etc...

If a town Xi is not visited you will suppose that the triangle

X0Xi-1Xi+1 is still a right triangle.

(Ref: https://en.wikipedia.org/wiki/Pythagoras#Pythagorean_theorem)

Task

Can you help your granny and give her the distance to travel?

Note

If you have some difficulty to see the tour I made a non terrific but maybe
useful drawing:

alternative text

Python Note

You must implement a function only, not a whole class.

All languages

The data type of the parameters can be seen in the examples test cases.

"tour" returns an int which is the floor of the total distance.
*/

#include "common.cpp"
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
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<string, double> stringdblmap;

class Solution {
public:
  static int tour_01(const vector<string> &fs, const vector<vector<string>> &ts,
                     const stringdblmap &h) {
    vector<string> ts_;
    for (auto &f : fs)
      for (auto &t : ts)
        if (f == t[0])
          ts_.push_back(t[1]);
    if (ts_.size() == 0)
      return 0;
    vector<int> ds;
    for (auto &t : ts_)
      for (auto &m : h)
        if (m.first == t)
          ds.push_back(m.second);
    if (ds.size() == 0)
      return 0;
    double ret = ds[0];
    for (int i = 1; i < ds.size(); ++i)
      ret += sqrt(ds[i] * ds[i] - ds[i - 1] * ds[i - 1]);
    return floor(ret + ds[ds.size() - 1]);
  }

  static int tour_02(const vector<string> &fs, const vector<vector<string>> &ts,
                     const stringdblmap &h) {
    unordered_map<string, string> m;
    for (auto &x : ts)
      m[x[0]] = x[1];
    double t = 0, ret = 0;
    for (auto &f : fs) {
      if (m.find(f) == m.end())
        continue;
      double d = h.at(m.at(f));
      ret += sqrt(d * d - t * t);
      t = d;
    }
    return int(ret + t);
  }
};

class TestCase {
public:
  const vector<string> fs;
  const vector<vector<string>> ts;
  const stringdblmap h;
  const int expected;
  TestCase(const vector<string> fs_, const vector<vector<string>> ts_,
           const stringdblmap h_, int expected_)
      : fs(fs_), ts(ts_), h(h_), expected(expected_) {
    // Constructor
  }
};

const vector<string> fs_g = {"A1", "A2", "A3", "A4", "A5"};
const vector<string> ts__g = {"X1", "X2", "X3", "X4", "X5"};
const vector<vector<string>> ts_g = {
    {"A1", "X1"}, {"A2", "X2"}, {"A3", "X3"}, {"A4", "X4"}, {"A5", "X5"}};

const vector<TestCase> set_gen(
    const function<int(const vector<string> &fs,
                       const vector<vector<string>> &ts, const stringdblmap &h)>
        &tour) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(10, 200);
  for (int i = 0; i < 100; ++i) {
    vector<string> fs = fs_g;
    random_shuffle(fs.begin(), fs.end());
    fs.erase(fs.end() - 1);
    vector<vector<string>> ts = ts_g;
    random_shuffle(ts.begin(), ts.end());
    ts.erase(ts.end() - 1);
    vector<string> ts_ = ts__g;
    random_shuffle(ts_.begin(), ts_.end());
    stringdblmap h;
    for (auto &t : ts_)
      h[t] = uni1(gen);
    int expected = tour(fs, ts, h);
    testcases.push_back(TestCase(fs, ts, h, expected));
  }
  return testcases;
}

void test(const function<int(const vector<string> &fs,
                             const vector<vector<string>> &ts,
                             const stringdblmap &h)> &tour,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const int actual = tour(testcase.fs, testcase.ts, testcase.h);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "	!!Assertion Failed!!" << endl;
      cout << "	in: " << vtos(testcase.fs) << " | " << endl;
      cout << "	out:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

unsigned long test_spd(const function<int(const vector<string> &fs,
                                          const vector<vector<string>> &ts,
                                          const stringdblmap &h)> &tour,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--)
      tour(testcase.fs, testcase.ts, testcase.h);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.tour_01);
  cout << "test..." << endl;
  cout << "tour_01" << endl, test(sol.tour_01, testcases);
  cout << "tour_02" << endl, test(sol.tour_02, testcases);
  cout << "test_spd..." << endl;
  cout << "tour_01:	" << test_spd(sol.tour_01, testcases) << "ms" << endl;
  cout << "tour_02:	" << test_spd(sol.tour_02, testcases) << "ms" << endl;
  return 0;
}
