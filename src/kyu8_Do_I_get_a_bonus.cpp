/*
https://www.codewars.com/kata/do-i-get-a-bonus

It's bonus time in the big city! The fatcats are rubbing their paws in
anticipation... but who is going to make the most money?

Build a function that takes in two arguments (salary, bonus). Salary will be an
integer, and bonus a boolean.

If bonus is true, the salary should be multiplied by 10. If bonus is false, the
fatcat did not make enough money and must receive only his stated salary.

Return the total figure the individual will receive as a string prefixed with
'£' (JS and Java) or '$' (C#, C++, Ruby, Elixir and Python).
*/

#include <cassert>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Solution {
 public:
  static string bonus_time_01(int salary, bool bonus) {
    stringstream ret;
    bonus ? ret << "$" << salary * 10 : ret << "$" << salary;
    return ret.str();
  };

  static string bonus_time_02(int salary, bool bonus) {
    return "$" + to_string(salary) + (bonus ? "0" : "");
  };
};

void test(string (*bonus_time)(int, bool)) {
  // ExampleTests
  assert(bonus_time(10000, true) == "$100000");
  assert(bonus_time(25000, true) == "$250000");
  assert(bonus_time(10000, false) == "$10000");
  assert(bonus_time(60000, false) == "$60000");

  // RandomTests
  function<string(int, bool)> solution = [](int salary, bool bonus) {
    salary *= bonus ? 10 : 1;
    return "$" + to_string(salary);
  };

  srand(time(0));
  for (int i = 0; i < 100; i++) {
    int randomSalary = rand() % 1000000;
    bool randomBonus = rand() % 2 == 0;

    assert(bonus_time(randomSalary, randomBonus) ==
           solution(randomSalary, randomBonus));
  }
}

int main() {
  Solution sol;
  test(sol.bonus_time_01);
  test(sol.bonus_time_02);
  return 0;
}