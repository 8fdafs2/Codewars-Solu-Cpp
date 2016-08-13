/*
https://www.codewars.com/kata/correct-the-time-string

A new task for you!

You have to create a method, that corrects a given time string. There was a
problem in addition, so many of the time strings are broken. Time-Format is
european. So from "00:00:00" to "23:59:59".

Some examples:

"09:10:01" -> "09:10:01"
"11:70:10" -> "12:10:10"
"19:99:99" -> "20:40:39"
"24:01:01" -> "00:01:01"

If the input-string is null or empty return exactly this value! (empty string
for C++)
If the time-string-format is invalid, return null. (empty string for C++)

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
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static string correct_01(string timeString) {
    if (timeString.empty()) return "";
    vector<int> time;
    stringstream ss(timeString);
    string token;
    while (getline(ss, token, ':')) {
      for (int i = 0; i < token.size(); i++)
        if (!isdigit(token[i])) return "";
      time.push_back(stoi(token));
    }
    if (time.size() != 3) return "";
    int carry = time[2] / 60;
    if (carry) time[2] %= 60;
    time[1] += carry;
    carry = time[1] / 60;
    if (carry) time[1] %= 60;
    time[0] += carry;
    if (time[0] > 23) time[0] %= 24;
    ss.str("");
    ss.clear();
    ss << setw(2) << setfill('0') << time[0] << ":" << setw(2) << time[1] << ":"
       << setw(2) << time[2];
    return ss.str();
  };

  static string correct_02(string timeString) {
    if (timeString.empty()) return "";
    vector<int> arr;
    size_t pos1 = 0;
    size_t pos2 = timeString.find(':');
    while (pos2 != string::npos) {
      string token{timeString.substr(pos1, pos2 - pos1)};
      for (int i = 0; i < token.size(); i++)
        if (!isdigit(token[i])) return "";
      arr.push_back(atoi(token.c_str()));
      pos1 = pos2 + 1;
      pos2 = timeString.find(':', pos2 + 1);
    }
    arr.push_back(
        atoi(timeString.substr(pos1, timeString.size() - pos1).c_str()));
    if (arr.size() != 3) return "";
    for (int i = arr.size() - 1; i > 0; i--) {
      arr[i - 1] += (arr[i] / 60);
      arr[i] %= 60;
    }
    arr[0] %= 24;
    string res = "";
    for (int i = 0; i < arr.size(); i++)
      res += (arr[i] < 10 ? "0" : "") + to_string(arr[i]) + ":";
    return res.substr(0, res.size() - 1);
  };
};

class TestCase {
 public:
  string timeString;
  string expected;
  TestCase(const string &timeString_, const string &expected_)
      : timeString(timeString_), expected(expected_) {
    // Constructor
  }
};

const vector<TestCase> set_gen(const function<string(string)> &correct) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int randomHour = rand() % 72 + 18;
    int randomMinute = rand() % 34 + 56;
    int randomSecond = rand() % 43 + 57;
    string timeString =
        (randomHour < 10 ? "0" : "") + to_string(randomHour) + ":" +
        (randomMinute < 10 ? "0" : "") + to_string(randomMinute) + ":" +
        (randomSecond < 10 ? "0" : "") + to_string(randomSecond);
    string expected = correct(timeString);
    testcases.push_back(TestCase(timeString, expected));
  }
  return testcases;
}

void test(const function<string(string)> &correct,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(correct(testcase.timeString) == testcase.expected);
  }
}

unsigned long test_spd(const function<string(string)> &correct,
                       const vector<TestCase> &testcases,
                       unsigned int ntimes = 1000) {
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = ntimes;
    chrono::high_resolution_clock::time_point t1 =
        chrono::high_resolution_clock::now();
    while (n--) correct(testcase.timeString);
    chrono::high_resolution_clock::time_point t2 =
        chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.correct_01);
  test(sol.correct_01, testcases);
  test(sol.correct_02, testcases);
  cout << "isAscOrder_01:\t" << test_spd(sol.correct_01, testcases) << "ms"
       << endl;
  cout << "isAscOrder_02:\t" << test_spd(sol.correct_02, testcases) << "ms"
       << endl;
  return 0;
}