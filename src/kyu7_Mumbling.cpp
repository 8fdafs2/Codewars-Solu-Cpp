/*
https://www.codewars.com/kata/mumbling

This time no story, no theory. The examples below show you how to write function
accum:

Examples:

Accumul::accum("abcd");    // "A-Bb-Ccc-Dddd"
Accumul::accum("RqaEzty"); // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
Accumul::accum("cwAt");    // "C-Ww-Aaa-Tttt"
The parameter of accum is a string which includes only letters from a..z and
A..Z.
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
  static string accum_01(const string &s) {
    string ret;
    int i(0);
    for (char c : s) {
      ret += toupper(c);
      ret += string(i++, tolower(c)) + "-";
    }
    return ret.substr(0, ret.length() - 1);
  };

  static string accum_02(const string &s) {
    stringstream result;
    for (int i = 0; i < s.length(); i++)
      result << "-" << string(1, toupper(s[i])) << string(i, tolower(s[i]));
    return result.str().substr(1);
  };

  static string accum_03(const string &s) {
    string r;
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      // 'A' -> 0x41 = 01000001
      // 'Z' -> 0x5A = 01011010
      // 'a' -> 0x61 = 01100001
      // 'z' -> 0x7A = 01111010
      // '_' -> 0x5F = 01011111
      // ' ' -> 0x20 = 00100000
      r += c & '_';
      c |= ' ';
      for (int j = 0; j < i; ++j) {
        r += c;
      }
      if (i < s.size() - 1) {
        r += "-";
      }
    }
    return r;
  };
};

string sol_(const string &s) {
  string ds;
  ds.resize(s.size());
  transform(s.begin(), s.end(), ds.begin(), ::tolower);
  string res = "";
  for (unsigned int i = 0; i < ds.size(); i++) {
    res += toupper(ds[i]);
    for (unsigned int j = 1; j < i + 1; j++) {
      res += ds[i];
    }
    res += string("-");
  }
  return res.substr(0, res.length() - 1);
}

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

string str_gen(int k) {
  int i = 0;
  string s = "";
  uniform_int_distribution<> dis1(0, 100);
  uniform_int_distribution<> dis2(97, 122);
  uniform_int_distribution<> dis3(65, 90);
  while (i < k) {
    if (dis1(gen) % 2 == 0)
      s += static_cast<char>(dis2(gen));
    else
      s += static_cast<char>(dis3(gen));
    i++;
  }
  return s;
}

void test(string (*accum)(const string &)) {
  // random test
  for (int i = 0; i < 200; i++) {
    uniform_int_distribution<int> uni1(10, 30);
    int rn = uni1(gen);
    string s = str_gen(rn);
    assert(accum(s) == sol_(s));
  }
}

int main() {
  Solution sol;
  test(sol.accum_01);
  test(sol.accum_02);
  test(sol.accum_03);
  return 0;
}