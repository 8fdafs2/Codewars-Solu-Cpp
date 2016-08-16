using namespace std;

class Arge {
 public:
  static int nbYear(int p0, double percent, int aug, int p);
};

int Arge::nbYear(int p0, double percent, int aug, int p) {
  if (p0 >= p) return 0;
  percent = (100 + percent) / 100;
  int pc = (p0 * percent + aug);
  double inc = (percent * (percent * p0 + aug - p0));
  int ret{1};
  while (pc < p) {
    pc += inc;
    inc *= percent;
    ++ret;
  }
  return ret;
}