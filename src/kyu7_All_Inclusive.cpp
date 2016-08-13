/*
https://www.codewars.com/kata/all-inclusive

Input:

a string strng
an array of strings arr
Output of function contain_all_rots(strng, arr) (or containAllRots or
contain-all-rots):

a boolean true if all rotations of strng are included in arr
false otherwise
Examples:

contain_all_rots(
  "bsjq", ["bsjq", "qbsj", "sjqb", "twZNsslC", "jqbs"]) -> true

contain_all_rots(
  "Ajylvpy", ["Ajylvpy", "ylvpyAj", "jylvpyA", "lvpyAjy", "pyAjylv", "vpyAjyl",
"ipywee"]) -> false)
Note:

Though not correct in a mathematical sense

we will consider that there are no rotations of strng == ""
and for any array arr: contain_all_rots("", arr) --> true
*/

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
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  static bool containAllRots_01(const string &strng,
                                const vector<string> &arr) {
    if (strng == "") return true;
    int l = strng.size();
    string s = strng;
    for (int i = 0; i < l - 1; i++) {
      s = s[l - 1] + s.substr(0, l - 1);
      bool ret_false = true;
      for (int j = 0; j < arr.size(); j++) {
        if (s == arr[j]) {
          ret_false = false;
          break;
        }
      }
      if (ret_false) return false;
    }
    return true;
  };

  static bool containAllRots_02(const string &strng,
                                const vector<string> &arr) {
    if (strng == "") return true;
    string s = strng;
    for (size_t i = 0; i < strng.length(); i++) {
      rotate(s.begin(), s.begin() + 1, s.end());
      if (find(arr.begin(), arr.end(), s) == arr.end()) return false;
    }
    return true;
  };

  static bool containAllRots_03(const string &strng,
                                const vector<string> &arr) {
    string s = strng;
    unordered_set<string> uset(arr.begin(), arr.end());
    for (int i = s.size() - 1; i >= 0; --i) {
      if (uset.find(s) == uset.end()) return false;
      rotate(s.begin(), s.begin() + 1, s.end());
    }
    return true;
  };

  static bool containAllRots_04(const string &strng,
                                const vector<string> &arr) {
    string s = strng;
    unordered_set<string> uset(arr.begin(), arr.end());
    for (int i = s.size() - 1; i >= 0; --i) {
      if (uset.find(s) == uset.end()) return false;
      s += s[0];
      s.erase(0, 1);
    }
    return true;
  };
};

class TestCase {
 public:
  const string strng;
  const vector<string> arr;
  bool expected;
  TestCase(const string &strng_, const vector<string> &arr_, bool expected_)
      : strng(strng_), arr(arr_), expected(expected_) {
    // Constructor
  }
};

vector<string> doAllRots(const string &strng) {
  vector<string> res = {};
  for (unsigned int i = 0; i < strng.length(); i++) {
    string r = strng.substr(i, strng.length()) + strng.substr(0, i);
    vector<string>::iterator it;
    it = find(res.begin(), res.end(), r);
    if (it == res.end()) res.push_back(r);
  }
  return res;
}

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);

string doStr(int k) {
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

vector<string> doEx(string s) {
  vector<string> arr = doAllRots(s);
  unsigned int rn = s.length();
  if (rn <= 11) {
    arr.pop_back();
    s = doStr(rn);
    arr.push_back(s);
    s = doStr(rn + 2);
    arr.push_back(s);
  }
  return arr;
}

const vector<TestCase> set_gen(
    const function<bool(const string, const vector<string>)> &containAllRots) {
  vector<TestCase> testcases;
  for (int i = 0; i < 200; i++) {
    uniform_int_distribution<int> uni1(8, 15);
    int rn = uni1(gen);
    string strng = doStr(rn);
    vector<string> arr = doEx(strng);
    bool expected = containAllRots(strng, arr);
    testcases.push_back(TestCase(strng, arr, expected));
  }
  return testcases;
}

void test(
    const function<bool(const string, const vector<string>)> &containAllRots,
    const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    // string strng = testcase.strng;
    // vector<string> arr = testcase.arr;
    // assert(containAllRots(strng, arr) == testcase.expected);
    assert(containAllRots(testcase.strng, testcase.arr) == testcase.expected);
  }
}

unsigned long test_spd(
    const function<bool(const string, const vector<string>)> &containAllRots,
    const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); i++) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--) {
      // string strng = testcase.strng;
      // vector<string> arr = testcase.arr;
      // containAllRots(strng, arr);
      containAllRots(testcase.strng, testcase.arr);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.containAllRots_01);
  test(sol.containAllRots_01, testcases);
  test(sol.containAllRots_02, testcases);
  test(sol.containAllRots_03, testcases);
  test(sol.containAllRots_04, testcases);
  cout << "containAllRots_01:\t" << test_spd(sol.containAllRots_01, testcases)
       << "ms" << endl;
  cout << "containAllRots_02:\t" << test_spd(sol.containAllRots_02, testcases)
       << "ms" << endl;
  cout << "containAllRots_03:\t" << test_spd(sol.containAllRots_03, testcases)
       << "ms" << endl;
  cout << "containAllRots_04:\t" << test_spd(sol.containAllRots_04, testcases)
       << "ms" << endl;
  return 0;
}