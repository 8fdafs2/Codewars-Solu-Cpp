#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  const std::size_t N = 5;
  int ar[N];
  std::generate_n(ar, N, std::rand);  // Using the C function rand()

  char str[5];
  generate_n(str, 5, '1');

  std::cout << "ar: ";
  std::copy(ar, ar + N, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}