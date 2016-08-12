/*
https://www.codewars.com/kata/weight-of-its-contents

Welcome to the Mathematics gameshow. I'm your host, Apex Rhombus, and it's time
for the lightning round!

Today we'll talk about a hypothetical bottle. This entire bottle weighs 120
grams. Its contents weigh twice as much as the bottle itself. What, may I ask,
do the contents weigh?

...Did you guess 80 grams? Correct! Now that you've got that idea, I'm gonna ask
you that question in 10 different ways so you'd better get ready!

Let's make a contentWeight function that takes in two parameters: bottleWeight
and scale. This function will return the weight of the contents inside the
bottle.

bottleWeight will be an integer representing the weight of the entire bottle
(contents included).

scale will be a string that you will need to parse. It will tell you how the
content weight compares to the weight of the bottle by itself. 2 times larger, 6
times larger, and 15 times smaller would all be valid strings (smaller and
larger are the only comparison words).

The first test case has been filled out for you. Good luck!
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
  static int content_weight_01(int bottle_weight, string scale) {
    istringstream iss(scale);
    vector<string> tokens;
    string buf;
    while (iss >> buf) tokens.push_back(buf);
    if (tokens[2] == "larger")
      return bottle_weight / (stoi(tokens[0]) + 1) * stoi(tokens[0]);
    return bottle_weight / (stoi(tokens[0]) + 1);
  };

  static int content_weight_02(int bottle_weight, string scale) {
    int s = stoi(scale);
    bool l = scale.find("larger") != string::npos;
    return bottle_weight * (l ? s : 1) / (s + 1);
  };

  static int content_weight_03(int bottle_weight, string scale) {
    int k = stoi(scale);
    return (scale[scale.size() - 3] == 'g') ? (k * bottle_weight) / (k + 1)
                                            : bottle_weight / (k + 1);
  };

  static int content_weight_04(int bottle_weight, string scale) {
    int x;
    string times, comparator;
    stringstream s(scale);
    s >> x >> times >> comparator;
    if (comparator == "larger") {
      return bottle_weight * x / (x + 1);
    } else {
      return bottle_weight / (x + 1);
    }
  };
};

vector<string> _split(string s) {
  istringstream iss(s);
  std::vector<string> tokens;
  do {
    string sub;
    iss >> sub;
    tokens.push_back(sub);
  } while (iss);
  return tokens;
}

int _content_weight(int bottle_weight, string scale) {
  vector<string> tokens = _split(scale);
  int multiplier = stoi(tokens[0]);
  string magnifier = tokens[2];
  return (bottle_weight / (multiplier + 1)) *
         (magnifier == "larger" ? multiplier : 1);
}

void test(int (*content_weight)(int, string)) {
  // random test
  for (int i = 0; i < 50; i++) {
    int weight = (rand() % 100 + 51) * 12;
    int scale_num = (rand() % 3 + 1);
    string magnifier = (rand() % 2 == 1) ? "larger" : "smaller";
    string scale = to_string(scale_num) + " times " + magnifier;
    int actual = content_weight(weight, scale);
    int expected = _content_weight(weight, scale);
    assert(actual == expected);
  }
}

int main() {
  Solution sol;
  test(sol.content_weight_01);
  test(sol.content_weight_02);
  test(sol.content_weight_03);
  test(sol.content_weight_04);
  return 0;
}