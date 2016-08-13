#include <cmath>
#include <string>

using namespace std;

class SumSquaredDivisors {
 public:
  static std::string listSquared(long long m, long long n);
};

string SumSquaredDivisors::listSquared(long long m, long long n) {
  string ret;
  if (m == 1) {
    ret += "{1, 1}, ";
    ++m;
  }
  for (int i = m; i <= n; i++) {
    int sum = 1 + i * i;
    double sqrt_i_f = sqrt(i);
    int sqrt_i_i = floor(sqrt_i_f);
    if (sqrt_i_f == sqrt_i_i) sum += i * i;
    for (int j = 2; j <= sqrt_i_i; j++)
      if (i % j == 0) sum += j * j + pow(i / j, 2);
    double sqrt_sum = sqrt(sum);
    if (floor(sqrt_sum) == sqrt_sum)
      ret += "{" + to_string(i) + ", " + to_string(sum) + "}, ";
  };
  return "{" + ret.substr(0, ret.size() - 2) + "}";
};