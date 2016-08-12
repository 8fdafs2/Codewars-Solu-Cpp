/*
Who likes keywords? Nobody likes keywords, so why use them?

You know what keyword I use too much? if! We should make a function called _if,
with its arguments as a logical test and two functions/lambdas where the first
function is executed if the boolean is true, and the second if it's false, like
an if/else statement, so that we don't have to mess around with those nasty
keywords! Even so, It should support truthy/falsy types just like the keyword.

Examples:

    void TheTrue() { std::cout << "true" }
    void TheFalse() { std::cout << "false" }
    _if(true, TheTrue, TheFalse);
    // Logs 'true' to the console.
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <string>

class Solution {
 public:
  static void _if_01(bool value, std::function<void(void)> func1,
                     std::function<void(void)> func2) {
    if (value) {
      func1();
    } else {
      func2();
    }
  };
  static void _if_02(bool value, std::function<void(void)> func1,
                     std::function<void(void)> func2) {
    value ? func1() : func2();
  }
};

bool ran_expected;
int run_times;
void Expected() {
  ran_expected = true;
  run_times++;
};
void Unexpected() {
  ran_expected = false;
  run_times++;
};

void test(void (*_if)(bool, std::function<void(void)>,
                      std::function<void(void)>)) {
  ran_expected = false;
  run_times = 0;
  // should_work_for_true
  _if(true, Expected, Unexpected);
  assert(ran_expected == true);
  assert(run_times == 1);

  ran_expected = false;
  run_times = 0;
  // should_work_for_false
  _if(false, Unexpected, Expected);
  assert(ran_expected == true);
  assert(run_times == 1);
}

int main() {
  Solution sol;
  test(sol._if_01);
  test(sol._if_02);
  return 0;
}