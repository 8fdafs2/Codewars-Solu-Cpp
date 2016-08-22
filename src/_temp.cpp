#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_map<string, double> stringdblmap;
class Tour {
public:
  static int tour(const vector<string> &fs, const vector<vector<string>> &ts,
                  const stringdblmap &h);
};

int Tour::tour(const vector<string> &fs, const vector<vector<string>> &ts,
               const stringdblmap &h) {
  vector<string> ts_;
  for (auto &f : fs)
    for (auto &t : ts)
      if (f == t[0])
        ts_.push_back(t[1]);
  if (ts_.size() == 0)
    return 0;
  vector<int> ds;
  for (auto &t : ts_) {
    auto t = h.find(t);
    if (t != h.end())
      ds.push_back(t->second);
  }
  if (ds.size() == 0)
    return 0;
  double ret = ds[0];
  for (int i = 1; i < ds.size(); ++i)
    ret += sqrt(ds[i] * ds[i] - ds[i - 1] * ds[i - 1]);
  return floor(ret + ds[ds.size() - 1]);
}
