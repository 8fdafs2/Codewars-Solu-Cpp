#include <string>

using namespace std;

class UpAndDown {
 public:
  static string arrange(const string &s);
};

string UpAndDown::arrange(const string &s) {
  vector<string> elems;
  stringstream ss(s);
  string item;
  while (getline(ss, item, ' ')) elems.push_back(item);
  int l = elems.size();
  if (l < 1) return "";
  for (int i = 0; i < l - 1; ++i)
    if (i % 2 == 0) {
      if (elems[i].size() > elems[i + 1].size()) swap(elems[i], elems[i + 1]);
    } else {
      if (elems[i].size() < elems[i + 1].size()) swap(elems[i], elems[i + 1]);
    }
  ss.clear();
  ss.str("");
  for (int i = 0; i < l; ++i) {
    if (i != 0) ss << " ";
    transform(elems[i].begin(), elems[i].end(), elems[i].begin(),
              i % 2 == 0 ? ::tolower : ::toupper);
    ss << elems[i];
  }
  return ss.str();
}