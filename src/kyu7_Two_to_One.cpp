/*
https://www.codewars.com/kata/two-to-one

Take 2 strings s1 and s2 including only letters from ato z. Return a new sorted
string, the longest possible, containing distinct letters, - each taken only
once - coming from s1 or s2.

Examples:

a = "xyaabbbccccdefww"
b = "xxxxyyyyabklmopq"
longest(a, b) -> "abcdefklmopqwxy"

a = "abcdefghijklmnopqrstuvwxyz"
longest(a, a) -> "abcdefghijklmnopqrstuvwxyz"
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static string longest_01(const string &s1, const string &s2) {
    string ret;
    string s = s1 + s2;
    for (int i = 0; i < s.length(); i++) {
      if (ret.find(s[i]) == string::npos) ret += s[i];
    }
    sort(ret.begin(), ret.end());
    return ret;
  };

  static string longest_02(const string &s1, const string &s2) {
    string ret = s1 + s2;
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
  };

  static string longest_03(const string &s1, const string &s2) {
    set<char> chars(s1.begin(), s1.end());
    for (char c : s2) chars.insert(c);
    return string(chars.begin(), chars.end());
  };
};

string sol_(const string &s1, const string &s2) {
  string s = s1 + s2;
  string a;
  for (auto c : "abcdefghijklmnopqrstuvwxyz") {
    if (s.find(c) != string::npos) a += c;
  }
  return a;
}

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
// random_device rd;
// mt19937 gen(rd());

string str_gen(int k) {
  int i = 0;
  string s;
  uniform_int_distribution<> dis(97, 122);
  while (i++ < k) {
    s += static_cast<char>(dis(gen));
  }
  return s;
}

void test(string (*longest)(const string &, const string &)) {
  // random test
  uniform_int_distribution<> uni1(1, 8);
  for (int i = 0; i < 200; i++) {
    int rn1 = uni1(gen);
    string a1 = str_gen(rn1);
    int rn2 = uni1(gen);
    string a2 = str_gen(rn2);
    assert(longest(a1, a2) == sol_(a1, a2));
  }
}

int main() {
  Solution sol;
  test(sol.longest_01);
  test(sol.longest_02);
  test(sol.longest_03);
  return 0;
}