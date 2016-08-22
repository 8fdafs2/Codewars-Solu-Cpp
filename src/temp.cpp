#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class RevRot {
public:
  static string revRot(const string &s, unsigned int sz);
};

string RevRot::revRot(const string &s, unsigned int sz) {
  if (sz <= 0 || s.empty() || sz > s.length())
    return "";
  string x = s.substr(0, sz);
  bool p = true;
  for (const char &c : x)
    if (c % 2 == 1) // '0' == 48, so 'digit' is even iff digit is even
      p = !p;
  if (p) {
    reverse(x.begin(), x.end());
    return x + revRot(s.substr(sz), sz);
  }
  x += x[0];
  return x.substr(1) + revRot(s.substr(sz), sz);
}
