/*
https://www.codewars.com/kata/find-maximum-and-minimum-values-of-a-list

Your task is to make two functions, max and min (maximum and minimum in PHP)
that take a(n) array/vector of integers list as input and outputs, respectively,
the largest and lowest number in that array/vector.

Examples

    max({4,6,2,1,9,63,-134,566}) returns 566
    min({-52, 56, 30, 29, -54, 0, -110}) returns -110
    max({5}) returns 5
    min({42, 54, 65, 87, 0}) returns 0

Notes

    You may consider that there will not be any empty arrays/vectors.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  static int min_01(vector<int> list) {
    return *min_element(begin(list), end(list));
  }
  static int max_01(vector<int> list) {
    return *max_element(begin(list), end(list));
  }

  static int min_02(vector<int> list) {
    int ret = list[0];
    for (int i = 1; i < list.size(); i++) {
      if (list[i] < ret) ret = list[i];
    }
    return ret;
  }
  static int max_02(vector<int> list) {
    int ret = list[0];
    for (int i = 1; i < list.size(); i++) {
      if (list[i] > ret) ret = list[i];
    }
    return ret;
  }
};

int sol1(vector<int> list) {
  int result = list[0];
  for (int i = 1; i < list.size(); i++) {
    if (result > list[i]) result = list[i];
  }
  return result;
}

int sol2(vector<int> list) {
  int result = list[0];
  for (int i = 1; i < list.size(); i++) {
    if (result < list[i]) result = list[i];
  }
  return result;
}

void test(int (*min)(vector<int>), int (*max)(vector<int>)) {
  //
  assert(min({-52, 56, 30, 29, -54, 0, -110}) == -110);
  assert(min({42, 54, 65, 87, 0}) == 0);
  assert(min({1, 2, 3, 4, 5, 10}) == 1);
  assert(min({-1, -2, -3, -4, -5, -10}) == -10);
  //
  assert(max({-52, 56, 30, 29, -54, 0, -110}) == 56);
  assert(max({4, 6, 2, 1, 9, 63, -134, 566}) == 566);
  assert(max({5}) == 5);
  assert(max({534, 43, 2, 1, 3, 4, 5, 5, 443, 443, 555, 555}) == 555);

  for (int i = 0; i < 10; i++) {
    int rand_lng = rand() % 15 + 1;
    vector<int> rand_list;
    for (int l = 0; l < rand_lng; l++) {
      rand_list.push_back(rand());
    }

    /*
    cout << "rand_lng: " << rand_lng << endl;
    cout << "rand_list: ";
    for (auto i = rand_list.begin(); i != rand_list.end(); i++)
      cout << *i << ' ';
    cout << endl;
    */

    assert(min(rand_list) == sol1(rand_list));
    assert(max(rand_list) == sol2(rand_list));
  }
}

int main() {
  Solution sol;
  test(sol.min_01, sol.max_01);
  test(sol.min_02, sol.max_02);
  return 0;
}