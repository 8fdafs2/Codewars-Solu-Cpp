/*
https://www.codewars.com/kata/count-of-positives-slash-sum-of-negatives

If the input array is empty or null, return an empty array:

C#: new int[] {} / new int[0];
C++: std::vector<int>();
JavaScript/CoffeeScript/PHP: [];
For example:

input vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -12, -13, -14, -15}
return vector<int>  {10, -65}.
*/

#include <cassert>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  static vector<int> countPositivesSumNegatives_01(vector<int> input) {
    vector<int> ret;
    if (input.empty()) return ret;
    ret.push_back(0);
    ret.push_back(0);
    for (int i = 0; i < input.size(); i++) {
      if (input[i] > 0)
        ret[0]++;
      else if (input[i] < 0)
        ret[1] += input[i];
    }
    return ret;
  }

  static vector<int> countPositivesSumNegatives_02(vector<int> input) {
    if (input.empty()) return {};
    int countPositives{0}, sumNegatives{0};
    for (int x : input)
      x > 0 ? countPositives++ : (x != 0 ? sumNegatives += x : 0);
    return {countPositives, sumNegatives};
  }

  static vector<int> countPositivesSumNegatives_03(vector<int> input) {
    if (input.empty()) return vector<int>();
    vector<int> ret(2);
    for (int i = 0; i < input.size(); i++) {
      if (input[i] > 0) {
        ret[0]++;
      } else {
        ret[1] += input[i];
      }
    }
    return ret;
  }
};

vector<int> solution(vector<int> input) {
  if (input.size() == 0) return vector<int>();
  vector<int> result(2, 0);
  for (int i = 0; i < input.size(); i++) {
    if (input[i] > 0) {
      result[0]++;
    } else {
      result[1] += input[i];
    }
  }
  return result;
}

void test(vector<int> (*countPositivesSumNegatives)(vector<int>)) {
  // Test1
  vector<int> expected{10, -65};
  vector<int> result = countPositivesSumNegatives(
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -11, -12, -13, -14, -15});
  assert(result[0] == expected[0]);
  assert(result[1] == expected[1]);
  // Test2
  expected = {8, -50};
  result = countPositivesSumNegatives(
      {0, 2, 3, 0, 5, 6, 7, 8, 9, 10, -11, -12, -13, -14});
  assert(result[0] == expected[0]);
  assert(result[1] == expected[1]);
  // Test3
  result = countPositivesSumNegatives(vector<int>());
  assert(result.size() == 0);
  // RandomTests
  for (int i = 0; i < 10; i++) {
    srand(time(0));
    int randomSize = rand() % 100;
    vector<int> randomInput;
    for (int i = 0; i < randomSize; i++) randomInput.push_back(rand() % 100);
    vector<int> expected = solution(randomInput);
    vector<int> actual = countPositivesSumNegatives(randomInput);
    assert(actual[0] == expected[0]);
    assert(actual[1] == expected[1]);
  }
}

int main() {
  Solution sol;
  test(sol.countPositivesSumNegatives_01);
  test(sol.countPositivesSumNegatives_02);
  test(sol.countPositivesSumNegatives_03);
  return 0;
}