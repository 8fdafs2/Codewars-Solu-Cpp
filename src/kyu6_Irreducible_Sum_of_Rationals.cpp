/*
https://www.codewars.com/kata/irreducible-sum-of-rationals

You will have a list of rationals in the form

m = [ [numer_1, denom_1] , ... , [numer_n, denom_n] ] or m = [ (numer_1,
denom_1) , ... , (numer_n, denom_n) ]

where all numbers are positive integers. You have to produce the sum N/D of
these rationals in an irreducible form ie N and D have only 1 for divisor.

The result will be written in the form

[N, D] in Ruby/Python/Clojure/JS/CS
Just "N D" in Haskell
"[N, D]" in Java, CSharp, TS
{N, D} in C++
{N, D} in Elixir
Example:

[ [1, 2], [1, 3], [1, 4] ] ---->
[13, 12] or: Just "13 12" (Haskell) or: "[13, 12]" (Java, CSharp, TS) or: {13,
12} (C++, Elixir)
Notes:

If m is [] return

nil/None/null (Ruby/Elixir/Clojure/Python/JS/CS/TS/Java/CSharp)
Nothing (Haskell)
{0, 1} (C++)
If D divise N return:

N/D as an integer: n (Ruby/Elixir/Clojure/Python/JS/CS)
Just "n" (Haskell), "n" (Java, CSharp, TS), {n, 1} (C++).
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
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  static pair<int, int> sumFracts_01(const vector<vector<int>> &l) {
    int n = 0;
    int d = 1;
    for (int i = 0; i < l.size(); i++) {
      const vector<int> &p = l[i];
      if (d != p[1]) {
        n = n * p[1] + d * p[0];
        d *= p[1];
      } else
        n += p[0];
    }
    function<int(int, int)> gcd = [&gcd](int a, int b) {
      return b == 0 ? a : gcd(b, a % b);
    };
    int gcd_ = gcd(n, d);
    n /= gcd_;
    d /= gcd_;
    return {n, d};
  };

  static pair<int, int> sumFracts_02(const vector<vector<int>> &l) {
    if (l.empty()) {
      return {0, 1};
    }
    function<int(int, int)> gcd = [](int x, int y) -> int {
      while (y != 0) {
        int t = x;
        x = y;
        y = t % y;
      }
      return x;
    };
    function<int(int, int)> lcm = [&gcd](int a, int b) -> int {
      return (a * b) / gcd(a, b);
    };
    function<int(const vector<vector<int>> &)> comDenom =
        [&lcm](const vector<vector<int>> &l) -> int {
      int result = l[0][1];
      for (int i = 1; i < l.size(); i++) {
        result = lcm(result, l[i][1]);
      }
      return result;
    };
    function<int(const vector<vector<int>> &)> sumNum =
        [&comDenom](const vector<vector<int>> &l) -> int {
      int lc = comDenom(l);
      int s = 0;
      for (int i = 0; i < l.size(); i++) {
        s += l[i][0] * lc / l[i][1];
      }
      return s;
    };
    int num = sumNum(l);
    int den = comDenom(l);
    // if (num % den == 0) {
    //   return {num / den, 1};
    // }
    int gd = gcd(num, den);
    return {num / gd, den / gd};
  };
};

class TestCase {
 public:
  vector<vector<int>> l;
  pair<int, int> expected;
  TestCase(const vector<vector<int>> &l_, const pair<int, int> &expected_)
      : l(l_), expected(expected_) {
    // Constructor
  }
};

random_device rd;
mt19937 rng(rd());

const vector<TestCase> set_gen(
    const function<pair<int, int>(const vector<vector<int>> &)> &sumFracts) {
  vector<TestCase> testcases;
  uniform_int_distribution<int> uni1(1, 50);
  for (int i = 0; i < 100; ++i) {
    int a = uni1(rng);
    vector<vector<int>> l = {{a + 1, a}, {a + 2, a + 1}, {a, a + 2}};
    pair<int, int> expected = sumFracts(l);
    testcases.push_back(TestCase(l, expected));
  }
  return testcases;
}

void test(
    const function<pair<int, int>(const vector<vector<int>> &)> &sumFracts,
    const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(sumFracts(testcase.l) == testcase.expected);
  }
}

unsigned long test_spd(
    const function<pair<int, int>(const vector<vector<int>> &)> &sumFracts,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) sumFracts(testcase.l);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.sumFracts_01);
  test(sol.sumFracts_01, testcases);
  test(sol.sumFracts_02, testcases);
  cout << "sumFracts_01:\t" << test_spd(sol.sumFracts_01, testcases) << "ms"
       << endl;
  cout << "sumFracts_02:\t" << test_spd(sol.sumFracts_02, testcases) << "ms"
       << endl;
  return 0;
}