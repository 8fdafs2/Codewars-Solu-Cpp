/*
https://www.codewars.com/kata/simple-encryption-number-1-alternating-split

For building the encrypted string:
Take every 2nd char from the string. Then the other chars.
Do this n times!

Examples:

"This is a test!", 1 -> "hsi  etTi sats!"
"This is a test!", 2 -> "hsi  etTi sats!" -> "s eT ashi tist!"
Write two methods:

std::string encrypt(std::string text, int n)
std::string decrypt(std::string encryptedText, int n)
For both methods:
If the input-string is null or empty return exactly this value!
If n is <= 0 then return the input text.

Have fun coding it and please don't forget to vote and rank this kata! :-)
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cmath>
#include <cstdlib>
#include <cstring>
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

int nloops(int l) {
  int l_h = l / 2, n = 1, p = l_h;
  while (p > 0) {
    p = (p % 2) ? (p >> 1) : ((p >> 1) + l_h);
    ++n;
  }
  return n;
}

class Solution {
 public:
  static string encrypt_01(const string &text, int n) {
    if (text.empty()) return text;
    if (n < 1) return text;
    const int l = text.length();
    char *t = (char *)text.c_str();
    while (n--) {
      char t_[l];
      strncpy(t_, t, l);
      int j = 0;
      for (int i = 1; i < l; i += 2, j++) t[j] = t_[i];
      for (int i = 0; i < l; i += 2, j++) t[j] = t_[i];
    }
    return string(t, l);
  };
  static string decrypt_01(const string &text, int n) {
    if (text.empty()) return text;
    if (n < 1) return text;
    const int l = text.length();
    char *t = (char *)text.c_str();
    while (n--) {
      char t_[l];
      strncpy(t_, t, l);
      int j = 0;
      for (int i = 1; i < l; i += 2, j++) t[i] = t_[j];
      for (int i = 0; i < l; i += 2, j++) t[i] = t_[j];
    }
    return string(t, l);
  };

  static string encrypt_02(const string &text, int n) {
    if (text.empty()) return text;
    if (n < 1) return text;
    const int l = text.length();
    string text_ = text;
    while (n--) {
      string s01, s02;
      for (int i = 0; i < l; i++) {
        if (i % 2 != 0)
          s01 += text_[i];
        else
          s02 += text_[i];
      }
      text_ = s01 + s02;
    }
    return text_;
  }
  static string decrypt_02(const string &text, int n) {
    if (text.empty()) return text;
    if (n < 1) return text;
    const int l = text.length();
    string text_ = text;
    const int l_half = l / 2;
    while (n--) {
      string s01;
      for (int i = 0, j = -1; i < l; i++) {
        if (j >= l_half)
          j -= l_half;
        else
          j += l_half + 1;
        s01 += text_[j];
      }
      text_ = s01;
    }
    return text_;
  };

  static string encrypt_03(const string &text, int n) {
    int l = text.size(), n_ = nloops(l);
    n %= n_;
    if (l < 2 || n < 1) return text;
    string str;
    for (int i = 1; i < l; i += 2) str += text[i];
    for (int i = 0; i < l; i += 2) str += text[i];
    return encrypt_03(str, n - 1);
  }
  static string decrypt_03(const string &text, int n) {
    int l = text.size(), n_ = nloops(l);
    n %= n_;
    if (l < 2 || n < 1) return text;
    return encrypt_03(text, n_ - n);
  }

  static string encrypt_04(const string &text, int n) {
    int l = text.size();
    if (l == 0 || n <= 0) return text;
    string text_ = text;
    for (int i = 0; i < n; i++) {
      string oddChars;
      string evenChars;
      for (int j = 0; j < l; j++)
        j % 2 == 1 ? oddChars.append(1, text_[j])
                   : evenChars.append(1, text_[j]);
      text_ = oddChars + evenChars;
    }
    return text_;
  }
  static string decrypt_04(const string &text, int n) {
    int l = text.size();
    if (l == 0 || n <= 0) return text;
    string text_ = text;
    for (int i = 0; i < n; i++) {
      string leftPart = text_.substr(0, l >> 1);
      string rightPart = text_.substr(l >> 1);
      text_ = "";
      for (int j = 0; j < l; j++)
        text_.append(1, j % 2 == 1 ? leftPart[j / 2] : rightPart[j / 2]);
    }
    return text_;
  }
};

class TestCase {
 public:
  string text;
  int n;
  string expected;
  TestCase(const string &text_, int n_, string &expected_)
      : text(text_), n(n_), expected(expected_) {
    // Constructor
  }
};

string generateRandomString() {
  string randomString;
  int randomStringSize = rand() % 11 + 1;
  for (int i = 0; i < randomStringSize; i++) {
    randomString.append(1, rand() % 26 + 65);
  }
  return randomString;
}

const vector<TestCase> set_gen(const function<string(string, int)> &encrypt) {
  vector<TestCase> testcases;
  srand(time(0));
  for (int i = 0; i < 100; i++) {
    string text = generateRandomString();
    int n = rand() % 10;
    string expected = encrypt(text, n);
    testcases.push_back(TestCase(text, n, expected));
  }
  return testcases;
}

void test(const function<string(string, int)> &encrypt,
          const function<string(string, int)> &decrypt,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    assert(encrypt(testcase.text, testcase.n) == testcase.expected);
    assert(decrypt(testcase.expected, testcase.n) == testcase.text);
  }
}

unsigned long test_spd(const function<string(string, int)> &encrypt,
                       const function<string(string, int)> &decrypt,
                       const vector<TestCase> &testcases,
                       unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) {
      encrypt(testcase.text, testcase.n);
      decrypt(testcase.expected, testcase.n);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.encrypt_01);
  test(sol.encrypt_01, sol.decrypt_01, testcases);
  test(sol.encrypt_02, sol.decrypt_02, testcases);
  test(sol.encrypt_03, sol.decrypt_03, testcases);
  test(sol.encrypt_04, sol.decrypt_04, testcases);
  cout << "encrypt_01 & decrypt_01:\t"
       << test_spd(sol.encrypt_01, sol.decrypt_01, testcases) << "ms" << endl;
  cout << "encrypt_02 & decrypt_02:\t"
       << test_spd(sol.encrypt_02, sol.decrypt_02, testcases) << "ms" << endl;
  cout << "encrypt_03 & decrypt_03:\t"
       << test_spd(sol.encrypt_03, sol.decrypt_03, testcases) << "ms" << endl;
  cout << "encrypt_04 & decrypt_04:\t"
       << test_spd(sol.encrypt_04, sol.decrypt_04, testcases) << "ms" << endl;
  return 0;
}