#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#define M_PI 3.14159265358979323846 /* pi */

using namespace std;

class PiApprox {
 public:
  static string iterPi(double epsilon);
};

string PiApprox::iterPi(double epsilon) {
  ostringstream ss;
  double pi = 0;
  int n = 1;
  double sign = 1.0;
  while (abs(4 * pi - M_PI) >= epsilon) {
    pi += sign / n;
    n += 2;
    sign = -sign;
  }
  ss << "[" << (n - 1) / 2 << ", " << setprecision(11) << 4 * pi << "]";
  return ss.str();
}