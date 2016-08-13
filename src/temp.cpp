/*
https://www.codewars.com/kata/simple-encryption-number-1-alternating-split

For building the encrypted string:
Take every 2nd char from the string. Then the other chars.
Do this n times!

Examples:

"This is a test!", 1 -> "hsi  etTi sats!"
"This is a test!", 2 -> "hsi  etTi sats!" -> "s eT ashi tist!"
Write two methods:

std::string encrypt(std::string text, int n)
std::string decrypt(std::string encryptedText, int n)
For both methods:
If the input-string is null or empty return exactly this value!
If n is <= 0 then return the input text.

Have fun coding it and please don't forget to vote and rank this kata! :-)
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int nloops(int l) {
  int l_h = l / 2, n = 1, p = l_h;
  while (p > 0) {
    p = (p % 2) ? (p >> 1) : ((p >> 1) + l_h);
    ++n;
  }
  return n;
}
string encrypt(const string &text, int n) {
  int l = text.size(), n_ = nloops(l);
  n %= n_;
  if (l < 2 || n < 1) return text;
  string str;
  for (int i = 1; i < l; i += 2) str += text[i];
  for (int i = 0; i < l; i += 2) str += text[i];
  return encrypt(str, n - 1);
}
string decrypt(const string &text, int n) {
  int l = text.size(), n_ = nloops(l);
  n %= n_;
  if (l < 2 || n < 1) return text;
  return encrypt(text, n_ - n);
}

string generateRandomString(int l) {
  string randomString;
  for (int i = 0, c = 65; i < l; i++, c++) {
    randomString.append(1, c);
  }
  return randomString;
}

void test(const function<string(string, int)> &encrypt) {
  for (int i = 2; i < 101; i += 2) {
    string text = generateRandomString(i);
    int n = 1;
    while (encrypt(text, n) != text) ++n;
    cout << text.size() << " | " << n << " | " << nloops(text.size()) << endl;
  }
}

int main() {
  test(encrypt);
  return 0;
}