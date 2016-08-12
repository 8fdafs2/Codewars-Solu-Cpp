/*
https://www.codewars.com/kata/complete-the-pattern-number-2

You have to write a function pattern which returns the following Pattern(See
Pattern & Examples) upto n number of rows.

Note:Returning the pattern is not the same as Printing the pattern.
Rules/Note:

If n < 1 then it should return "" i.e. empty string.
There are no whitespaces in the pattern.
Pattern:

(n)(n-1)(n-2)...4321
(n)(n-1)(n-2)...432
(n)(n-1)(n-2)...43
(n)(n-1)(n-2)...4
...............
..............
(n)(n-1)(n-2)
(n)(n-1)
(n)
Examples:

pattern(4):

4321
432
43
4
pattern(11):

1110987654321
111098765432
11109876543
1110987654
111098765
11109876
1110987
111098
11109
1110
11
Hint: Use \n in string to jump to next line
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
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
  static string pattern_01(int n) {
    if (n < 1) return "";
    vector<string> seq(n);
    for (int i = 0; i < n; i++) seq[i] = to_string(n - i);
    string ret = "";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - i; j++) ret += seq[j];
      ret += "\n";
    }
    return ret.substr(0, ret.length() - 1);
  };

  static string pattern_02(int n) {
    if (n < 1) return "";
    stringstream ss;
    for (int j = 0; j < n; j++) {
      for (int i = n; i > j; i--) ss << i;
      ss << "\n";
    }
    string ret = ss.str();
    return ret.substr(0, ret.size() - 1);
  };

  static string pattern_03(int n) {
    if (n < 1) return "";
    vector<int> seq(n);
    for (int i = 0; i < n; i++) seq[i] = n - i;
    string ret = "";
    for (int i = 0; i < n; i++) {
      ostringstream oss_;
      copy(seq.begin(), seq.end() - i, ostream_iterator<int>(oss_));
      ret += oss_.str() + "\n";
    }
    ret.erase(ret.length() - 1);
    return ret;
  };
};

void test(string (*pattern)(int)) {
  function<string(int)> checker = [](int n) {
    string result{};
    if (n < 1) return result;
    for (int i{1}; i <= n; ++i) {
      for (int j{n}; j >= i; --j) {
        result.append(to_string(j));
      }
      if (i != n) result.append("\n");
    }
    return result;
  };
  // random test
  srand(time(NULL));
  for (int index{0}; index < 100; ++index) {
    int input = rand() % 101;
    string actual = pattern(input);
    string expected = checker(input);
    assert(actual == expected);
  }
}

int main() {
  Solution sol;
  test(sol.pattern_01);
  test(sol.pattern_02);
  test(sol.pattern_03);
  return 0;
}