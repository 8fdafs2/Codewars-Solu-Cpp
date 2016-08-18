#include <algorithm>
#include <vector>

using namespace std;

class SqProd2Sum {
 public:
  static vector<pair<long, long>> prod2Sum(long long a, long long b,
                                           long long c, long long d);
};

vector<pair<long, long>> SqProd2Sum::prod2Sum(long long a, long long b,
                                              long long c, long long d) {
  long ac{a * c}, bd{b * d}, ad{a * d}, bc{b * c};
  long e1 = abs(ac + bd);
  long f1 = abs(ad - bc);
  long e2 = abs(ac - bd);
  long f2 = abs(ad + bc);
  if (e1 > f1) swap(e1, f1);
  if (e2 > f2) swap(e2, f2);
  if (e1 == e2) return {{e1, f1}};
  if (e1 < e2) return {{e1, f1}, {e2, f2}};
  return {{e2, f2}, {e1, f1}};
}