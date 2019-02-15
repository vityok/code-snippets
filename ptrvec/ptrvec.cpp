// TODO work in progress

#include <memory>
#include <vector>
#include <iostream>

int square(int num)
{
    std::vector<std::unique_ptr<int>> vec;

    for (auto i = 0; i < 10; ++i) {
        auto tmp = std::make_unique<int>(i);
        vec.push_back(std::move(tmp));
    }

    for (auto i = 0; i < vec.size(); ++i) {
	std::cout << *(vec[i]) << ", ";
    }
    std::cout << std::endl;

    return num * num;
}

int main()
{
    std::cout << square(10) << std::endl;
    return 0;
}

// g++ -Wall -pedantic -o ptrvec -std=c++14 ptrvec.cpp
// clang -o ptrvec -std=c++14 ptrvec.cpp

