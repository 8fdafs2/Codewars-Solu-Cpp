/*
https://www.codewars.com/kata/5616868c81a0f281e500005c

To participate in a prize draw each one gives his/her firstname.

Each letter of a firstname has a value which is its rank in the English
alphabet. A and a have rank 1, B and b rank 2 and so on.

The length of the firstname is added to the sum of these ranks hence a number n.
An array of random weights is linked to the firstnames and each n is multiplied
by its corresponding weight to get what they call a winning number.

Example: names: COLIN,AMANDBA,AMANDAB,CAROL,PauL,JOSEPH weights: [1, 4, 4, 5, 2,
1]

PAUL -> n = length of firstname + 16 + 1 + 21 + 12 = 4 + 50 -> 54 The weight
associated with PAUL is 2 so Paul's winning number is 54 * 2 = 108.

Now one can sort the firstnames in decreasing order of the winning numbers. When
two people have the same winning number sort them alphabetically by their
firstnames.

Task:

parameters: st a string of firstnames, we an array of weights, n a rank

return: the firstname of the participant whose rank is n (ranks are numbered
from 1)

Example:

names: COLIN,AMANDBA,AMANDAB,CAROL,PauL,JOSEPH weights: [1, 4, 4, 5, 2, 1] n: 4

The function should return: PauL

Note:

If st is empty return "No participants".

If n is greater than the number of participants then return "Not enough
participants".
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
#include <vector>

using namespace std;

class Solution {
public:
  static vector<string> split_01(const string &s, char delim) {
    vector<string> out;
    istringstream ss(s);
    string next;
    while (getline(ss, next, delim))
      out.push_back(next);
    return out;
  }
  static string nthRank_01(const string &st, const vector<int> &we, int n) {
    if (st.empty())
      return "No participants";
    vector<string> names = split_01(st, ',');
    int l = names.size();
    if (n > l)
      return "Not enough participants";
    vector<int> ranks(l);
    for (int i = 0; i < l; ++i) {
      string &name = names[i];
      int rank = name.size() * 2;
      for (auto c : name)
        rank += toupper(c) - 'A';
      ranks[i] = rank * we[i];
    }
    vector<string> ret{names};
    sort(ret.begin(), ret.end(),
         [ranks, names](const string &a, const string &b) {
           int r_a = ranks[find(names.begin(), names.end(), a) - names.begin()];
           int r_b = ranks[find(names.begin(), names.end(), b) - names.begin()];
           return r_a != r_b ? r_a < r_b : a > b;
         });
    return ret[l - n];
  }
  static string nthRank_02(const string &st, const vector<int> &we, int n) {
    if (st.empty())
      return "No participants";
    vector<string> names;
    int l = st.size();
    int p_s{-1};
    int p_e;
    do {
      p_e = st.find(',', ++p_s);
      if (p_e == string::npos) {
        names.push_back(st.substr(p_s));
        break;
      }
      names.push_back(st.substr(p_s, p_e - p_s));
      p_s = p_e;
    } while (1);
    l = names.size();
    if (n > l)
      return "Not enough participants";
    vector<pair<int, string>> ranks(l);
    for (int i = 0; i < l; ++i) {
      string &name = names[i];
      int rank = name.size() * 2;
      for (auto c : name)
        rank += toupper(c) - 'A';
      ranks[i] = {rank * we[i], name};
    }
    sort(
        ranks.begin(), ranks.end(),
        [ranks, names](const pair<int, string> &a, const pair<int, string> &b) {
          return a.first != b.first ? a.first < b.first : a.second > b.second;
        });
    return ranks[l - n].second;
  }
};

class TestCase {
public:
  const string st;
  const vector<int> we;
  const int n;
  const string expected;
  TestCase(const string st_, const vector<int> we_, int n_,
           const string &expected_)
      : st(st_), we(we_), n(n_), expected(expected_) {
    // Constructor
  }
};

const string st_g =
    "Sophia,Jacob,Isabella,Mason,Emma,William,Willaim,Olivia,Olivai,Jayden,Ava,"
    "Noah,Naoh,Emily,Michael,Abigail,Ethan,Madison,"
    "Alexander,Mia,Aiden,Chloe,Daniel,Elizabeth,Robert,Ella,Matthew,Addison,"
    "Elijah,Natalie,Joshua,Lily,Lyli,Liam,Grace,Andrew,Samantha,"
    "James,Avery,David,Sofia,Benjamin,Aubrey,Logan,Lagon,xxxxx,yyyyy,zzzzz";
vector<string> names_g = split(st_g, ',');

const vector<TestCase>
set_gen(const function<string(const string &st, const vector<int> &we, int n)>
            &nthRank) {
  vector<TestCase> testcases;
  random_shuffle(names_g.begin(), names_g.end());
  uniform_int_distribution<int> uni1(0, names_g.size());
  uniform_int_distribution<int> uni2(1, 20);
  for (int i = 0; i < 100; ++i) {
    int l = uni1(gen);
    vector<string> names;
    vector<int> we;
    while (l--) {
      names.push_back(names_g[l]);
      we.push_back(uni2(gen));
    }
    string st = join(names);
    int n = uni2(gen);
    string expected = nthRank(st, we, n);
    testcases.push_back(TestCase(st, we, n, expected));
  }
  return testcases;
}

void test(const function<string(const string &st, const vector<int> &we, int n)>
              &nthRank,
          const vector<TestCase> &testcases) {
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    const string &actual = nthRank(testcase.st, testcase.we, testcase.n);
    try {
      Assert<Wrong>(actual == testcase.expected);
    } catch (Wrong &e) {
      cout << "	!!Assertion Failed!!" << endl;
      cout << "	in: " << testcase.st << " | " << vtos(testcase.we) << " | "
           << testcase.n << endl;
      cout << "	out:" << actual << " vs. " << testcase.expected << endl;
    }
  }
}

unsigned long
test_spd(const function<string(const string &st, const vector<int> &we, int n)>
             &nthRank,
         const vector<TestCase> &testcases, unsigned int n_ = 1000) {
  using namespace chrono;
  unsigned long elapsed = 0;
  for (int i = 0; i < testcases.size(); ++i) {
    const TestCase &testcase = testcases[i];
    unsigned int n = n_;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while (n--)
      nthRank(testcase.st, testcase.we, testcase.n);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    elapsed += duration_cast<milliseconds>(t2 - t1).count();
  }
  return elapsed;
}

int main() {
  Solution sol;
  const vector<TestCase> &testcases = set_gen(sol.nthRank_01);
  cout << "test..." << endl;
  cout << "nthRank_01" << endl, test(sol.nthRank_01, testcases);
  cout << "nthRank_02" << endl, test(sol.nthRank_02, testcases);
  cout << "test_spd..." << endl;
  cout << "nthRank_01:	" << test_spd(sol.nthRank_01, testcases) << "ms"
       << endl;
  cout << "nthRank_02:	" << test_spd(sol.nthRank_02, testcases) << "ms"
       << endl;
  return 0;
}
