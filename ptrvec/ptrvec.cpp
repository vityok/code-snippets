// TODO work in progress

#include <memory>
#include <vector>
#include <iostream>

int square(int num)
{
    std::unique_ptr<int> upr(new int);

    std::vector<std::unique_ptr<int>> vec(10);
    for (auto i = 0; i < vec.size(); ++i) {
        auto tmp = std::make_unique<int>(i);
        vec.push_back(std::move(tmp));
    }
    for (auto i = 0; i < vec.size(); ++i) {
	std::cout << *vec[i] << " ";
    }
    std::cout << std::endl;
    return num * num;
}

int main()
{
    square(10);
    return 0;
}

// g++ -o ptrvec ptrvec.cpp
// clang -o ptrvec ptrvec.cpp

