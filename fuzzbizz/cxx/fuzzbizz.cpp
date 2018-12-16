#include <iostream>

void fuzzbizz(const int lim)
{
  for (int num = 1; num <= lim; ++ num) {
    bool div3 = ((num % 3) == 0);
    bool div5 = ((num % 5) == 0);

    if (div3 && div5) {
      std::cout << "fuzzbizz" << std::endl;
    } else if (div3) {
      std::cout << "fuzz" << std::endl;
    } else if (div5) {
      std::cout << "bizz" << std::endl;
    } else {
      std::cout << num << std::endl;
    }
  }
}

int main()
{
  fuzzbizz(100);
  return 0;
}

// g++ -Wall -Wextra -pedantic -o fuzzbizz fuzzbizz.cpp
