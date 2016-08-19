#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rainfall {
 public:
  static vector<double> datget(const string &town, const string &strng);
  static double mean(const string &town, const string &strng);
  static double variance(const string &town, const string &strng);
};

vector<double> Rainfall::datget(const string &town, const string &strng) {
  size_t pos_s = strng.find(town + ':');
  vector<double> dat;
  if (pos_s == string::npos) return dat;
  pos_s += town.size() + 1;
  size_t pos_e = strng.find('\n', pos_s);
  if (pos_e == string::npos) pos_e = strng.size();
  size_t pos_d;
  while (1) {
    pos_d = strng.find(' ', pos_s + 1);
    pos_s = strng.find(',', pos_d + 1);
    if (pos_s > pos_e) {
      dat.push_back(stod(strng.substr(pos_d + 1, pos_e - pos_d - 1)));
      break;
    }
    dat.push_back(stod(strng.substr(pos_d + 1, pos_s - pos_d - 1)));
  }
  return dat;
}

double Rainfall::mean(const string &town, const string &strng) {
  const vector<double> &dat = datget(town, strng);
  if (dat.empty()) return -1;
  size_t l = dat.size();
  double sum{0};
  for (size_t i = 0; i < l; ++i) sum += dat[i];
  return sum / l;
}
double Rainfall::variance(const string &town, const string &strng) {
  const vector<double> &dat = datget(town, strng);
  if (dat.empty()) return -1;
  size_t l = dat.size();
  double sum{0};
  for (size_t i = 0; i < l; ++i) sum += dat[i];
  double mea = sum / l;
  sum = 0;
  for (size_t i = 0; i < l; ++i) sum += pow(dat[i] - mea, 2);
  return sum / l;
}