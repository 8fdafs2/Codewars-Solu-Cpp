/*
https://www.codewars.com/kata/sum-of-the-first-nth-term-of-series

Task:

    Your task is to write a function which returns the sum of following series
    upto nth term(parameter).

    Series: 1 + 1/4 + 1/7 + 1/10 + 1/13 + 1/16 +...

Rules:

    You need to round the answer upto 2 decimal places and return it as String.
    If the given value is 0 then it should return 0.00
    You will only be given Natural Numbers as arguments.

Examples:

    SeriesSum(1) => 1 = "1"
    SeriesSum(2) => 1 + 1/4 = "1.25"
    SeriesSum(5) => 1 + 1/4 + 1/7 + 1/10 + 1/13 = "1.57"
*/

#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Solution {
 public:
  static string seriesSum_01(int n) {
    double ret = 0.0;
    double base = 1;
    while (n--) {
      ret += 1 / base;
      base += 3;
    }
    stringstream retss;
    retss << setprecision(2) << fixed << ret;
    return retss.str();
  };

  static string seriesSum_02(int n) {
    if (n == 0) return "0.00";
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
      sum += 1.0 / double(1 + 3 * i);
    }
    char buffer[20];
    sprintf(buffer, "%.2f", sum);
    string output = buffer;
    return output;
  };

  static string seriesSum_03(int n) {
    if (n == 0) return "0.00";
    double sum = 1;
    for (int i = 1; i < n; i++) sum += (double)1 / (1 + (3 * i));
    sum = round(sum * 100) / 100;
    string str = to_string(sum);
    return str.substr(0, 4);
  };
};

void test(string (*seriesSum)(int)) {
  function<string(int)> solution = [](int n) {
    string result = "0.00";
    if (n == 0) return result;
    double sum = 1;
    for (int i = 0; i < n - 1; i++) sum += 1.0 / (4 + 3 * i);
    stringstream ss;
    ss << fixed << setprecision(2) << sum;
    return ss.str();
  };
  // carpet test
  for (int i = 0; i < 1000; i++) {
    assert(seriesSum(i) == solution(i));
  }
}

int main() {
  Solution sol;
  test(sol.seriesSum_01);
  test(sol.seriesSum_02);
  test(sol.seriesSum_03);
  return 0;
}