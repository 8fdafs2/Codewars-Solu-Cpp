#include <vector>

using namespace std;

class RemovedNumbers {
 public:
  static vector<vector<long long>> removNb(long long n);
};

vector<vector<long long>> RemovedNumbers::removNb(long long n) {
  long long sum{(1 + n) * n / 2};
  vector<vector<long long>> ret;
  long long i = 1;
  while (i < n) {
    --sum;
    long long x = i * (i + 1);
    long long j = i + 1;
    while (j <= n) {
      // cout << i << " | " << j << endl;
      if (sum - j == x) {
        ret.push_back({i, j});
        ret.push_back({j, i});
        break;
      }
      if (sum - i < x) break;
      ++j;
      x += i;
    }
    ++i;
  }
  return ret;
}

vector<vector<long long>> RemovedNumbers::removNb(long long n) {
  long long a{(((1 + n) * n) >> 1) - 2};
  vector<vector<long long>> ret;
  long long b{3};
  while (b < n + 1) {
    // cout << a << '/' << b << endl;
    if (a < b) break;
    if (a % b != 0) {
      ++b;
      --a;
      continue;
    }
    if (b * n >= a) {
      ret.push_back({b - 1, a / b});
      // ret.push_back({a / b, b - 1});
    }
    ++b;
    --a;
  }
  return ret;
}