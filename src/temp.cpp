#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ToSmallest {
 public:
  static vector<long long> smallest(long long n);
};

vector<long long> ToSmallest::smallest(long long n) {
  cout << n << endl;
  string s = to_string(n), tmp = s;
  vector<long long> mem = {-1, -1, -1};
  unsigned int l = s.length();
  for (unsigned int i = 0; i < l; i++) {
    char c = s[i];
    string str1 = s.substr(0, i) + s.substr(i + 1, l - (i + 1));
    cout << "\tstr1: " << str1 << endl;
    for (unsigned int j = 0; j < l; j++) {
      string str2 = str1.substr(0, j) + c + str1.substr(j, str1.length() - j);
      cout << "\t\tstr2: " << str2 << endl;
      if (str2 < tmp) {
        tmp = str2;
        mem[0] = stoll(tmp);
        mem[1] = i;
        mem[2] = j;
      }
    }
  }
  if (mem[0] == -1) {
    mem[0] = n;
    mem[1] = 0;
    mem[2] = 0;
  }
  return mem;
}

int main() {
  ToSmallest ts;
  vector<long long> seq{
      1348787, 1015920,
  };
  for (auto n : seq) {
    vector<long long> ret = ts.smallest(n);
    cout << ret[0] << '|' << ret[1] << '|' << ret[2] << endl;
  }
  return 0;
}