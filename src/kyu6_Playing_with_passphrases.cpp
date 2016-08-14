/*
https://www.codewars.com/kata/playing-with-passphrases

Everyone knows passphrases. One can choose passphrases from poems, songs, movies
names and so on but frequently they can be guessed due to common cultural
references. You can get your passphrases stronger by different means. One is the
following:

choose a text in capital letters including or not digits and non alphabetic
characters,

shift each letter by a given number but the transformed letter must be a letter
(circular shift),
replace each digit by its complement to 9,
keep such as non alphabetic and non digit characters,
downcase each letter in odd position, upcase each letter in even position (the
first character is in position 0),
reverse the whole result.
Example:

your text: "BORN IN 2015!", shift 1

1 + 2 + 3 -> "CPSO JO 7984!"

4 "CpSo jO 7984!"

5 "!4897 Oj oSpC"

With longer passphrases it's better to have a small and easy program. Would you
write it?

https://en.wikipedia.org/wiki/Passphrase
*/

#include <algorithm>
#include <cassert>
#include <cctype>
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
  static string playPass_01(const string &s, int n) {
    string ret;
    for (int i = 0, c; i < s.size(); i++) {
      c = s[i];
      if ('A' <= c && c <= 'Z') {
        ret += ((c - 'A' + n) % 26 + ((i % 2 == 0) ? 'A' : 'a'));
      } else if ('0' <= c && c <= '9') {
        ret += (9 - (c - '0') + '0');
      } else
        ret += (c);
    }
    reverse(ret.begin(), ret.end());
    return ret;
  };

  static string playPass_02(const string &s, int n) {
    const int l = s.size();
    char ret[l];
    for (int i = l - 1, c, j = 0; i > -1; i--, j++) {
      c = s[i];
      if ('A' <= c && c <= 'Z') {
        ret[j] = ((c - 'A' + n) % 26 + ((i % 2 == 0) ? 'A' : 'a'));
      } else if ('0' <= c && c <= '9') {
        ret[j] = (9 - (c - '0') + '0');
      } else
        ret[j] = (c);
    }
    return string(ret, l);
  };
};

class TestCase {
 public:
  string s;
  int n;
  string expected;
  TestCase(const string &s_, int n_, const string &expected_)
      : s(s_), n(n_), expected(expected_) {
    // Constructor
  }
};

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

string doStr(int k) {
  int i = 0;
  string s;
  uniform_int_distribution<> dis1(0, 100);
  uniform_int_distribution<> dis2(48, 57);
  uniform_int_distribution<> dis3(65, 90);
  while (i++ < k) s += dis1(gen) % 2 == 0 ? dis2(gen) : dis3(gen);
  return s;
}

const vector<TestCase> set_gen(
    const function<string(const string, int)> &playPass) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    uniform_int_distribution<int> uni1(30, 50);
    uniform_int_distribution<int> uni2(2, 15);
    string s = doStr(uni1(gen));
    int n = uni2(gen);
    string expected = playPass(s, n);
    testcases.push_back(TestCase(s, n, expected));
  }
  return testcases;
}

void test(const function<string(const string, int)> &playPass,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(playPass(testcase.s, testcase.n) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(const string, int)> &playPass,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) playPass(testcase.s, testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.playPass_01);
  test(sol.playPass_01, testcases);
  test(sol.playPass_02, testcases);
  cout << "playPass_01:\t" << test_spd(sol.playPass_01, testcases) << "ms"
       << endl;
  cout << "playPass_02:\t" << test_spd(sol.playPass_02, testcases) << "ms"
       << endl;
  return 0;
}