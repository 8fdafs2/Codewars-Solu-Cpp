#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string vowelShift(const string &text, int n) {
  string ret(text);
  int l = text.size();
  if (l < 2 || n == 0) return ret;
  const string vowels{"aAeEiIoOuU"};
  vector<pair<int, char>> tab;
  for (int i = 0; i < l; ++i)
    if (vowels.find(text[i]) != string::npos) tab.push_back({i, text[i]});
  l = tab.size();
  while (n < 0) n += l;
  for (int i = 0; i < l; ++i) ret[tab[(i + n) % l].first] = tab[i].second;
  return ret;
}

int main() {
  cout << vowelShift("This is a test!", 1) << endl;

  return 0;
}