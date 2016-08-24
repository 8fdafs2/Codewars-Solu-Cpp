#include <cmath>

using namespace std;
typedef long long ll;

class BackWardsPrime {
 public:
  static string backwardsPrime(ll start, ll end);
};

bool is_prime(ll n) {
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  int root = sqrt(n);
  for (int i = 3; i < root + 1; i += 2)
    if ((n % i) == 0) return false;
  return true;
}

string BackWardsPrime::backwardsPrime(ll start, ll end) {
  string ret;
  for (ll i = start; i <= end; ++i) {
    string i_str = to_string(i);
    reverse(i_str.begin(), i_str.end());
    ll i_reversed = stoll(i_str);
    if (i != i_reversed && is_prime(i) && is_prime(i_reversed))
      ret += to_string(i) + " ";
  }
  return ret.substr(0, ret.size() - 2);
}