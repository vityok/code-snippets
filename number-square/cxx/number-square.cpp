// find all 3-digit numbers that have same last three digits when
// squared
//
// for example: 205^2=42025 and has same three digits in its suffix

// найти все тризначные числа, которые в квадрате имеют такие же три
// последних цифры

#include <string>
#include <iostream>

using std::string;

const string total_match_pattern("___");

bool same_chars(const string& a, string b) {
  for (char chk : a) {
    auto pos = b.find(chk); 
    if (pos == std::string::npos) {
      return false;
    } else {
      b[pos] = '_';
    }
  }
  return b.compare(total_match_pattern) == 0;
}

bool endswith(int key, int num)
{
  string skey = std::to_string(key);
  string snum = std::to_string(num);
  int last_three = snum.length() - 3;
  return same_chars(skey, snum.substr(last_three));
}

int main()
{
  for (int i = 100, n = 1; i < 999; ++i) {
    if (endswith(i, i*i)) {
      std::cout << n++ << ": " << i << " " << i*i << std::endl;
    }
  }
}

// g++ -Wall -Wextra -pedantic -std=c++14 -o number-square number-square.cpp
