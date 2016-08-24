#include <cmath>
#include <iostream>
#include <vector>

typedef unsigned long long ull;

using namespace std;

class ProdFib {
 public:
  static vector<ull> productFib(ull prod);
};

vector<ull> ProdFib::productFib(ull prod) {
  double gr = (1 + sqrt(5)) / 2;
  int n = round((log(5 * prod) / log(gr) - 1) / 2);
  ull fn = round(pow(gr, n) / sqrt(5));
  ull fn1 = round(fn * gr);
  while (fn * fn1 < prod) {
    fn = fn1;
    fn1 = round(fn * gr);
  }
  return {fn, fn1, fn * fn1 == prod};
}

main() {
  ProdFib pf;
  vector<ull> r;
  r = pf.productFib(4895);
  cout << r[0] << '|' << r[1] << '|' << r[2] << endl;  // {55, 89, true}
  r = pf.productFib(5895);
  cout << r[0] << '|' << r[1] << '|' << r[2] << endl;  // {89, 144, false}
  r = pf.productFib(74049690);
  cout << r[0] << '|' << r[1] << '|' << r[2] << endl;  // {6765, 10946, 1ULL}
  r = pf.productFib(84049690);
  cout << r[0] << '|' << r[1] << '|' << r[2] << endl;  // {10946, 17711, 0ULL}
}