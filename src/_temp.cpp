#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class MaxRotate {
 public:
  static long long maxRot(long long n);
};

long long MaxRotate::maxRot(long long n) {
  string n_str = to_string(n);
  size_t l = n_str.size();
  long long base0 = pow(10, l);
  long long base1 = 10;
  long long ret(n);
  for (size_t i = 1; i < l; ++i) {
    long long n_ = n / base0 * base0;
    n = n % base0;
    base0 /= 10;
    n = n_ + n % base0 * 10 + n / base0;
    if (ret < n) ret = n;
  }
  return ret;
}

void dotest(long long n, long long expected) {
  cout << MaxRotate::maxRot(n) << " | " << expected << endl;
}

int main() {
  dotest(56789, 0);
  // dotest(195881031, 988103115);
  // dotest(896219342, 962193428);
  // dotest(69418307, 94183076);
}
