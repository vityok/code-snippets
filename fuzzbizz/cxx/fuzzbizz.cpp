// -*- c-default-style: "linux"; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: nil -*-
#include <iostream>
#include <sstream>

const int ITER = 100;
const int MAX_NUM = 10000;

void fuzzbizz_inc(std::ostream& os, const int lim)
{
    os << "inc" << std::endl;
    os << "1" << std::endl;
    if (lim < 2) { return; }
    os << "2" << std::endl;
    if (lim < 3) { return; }
    os << "fuzz" << std::endl;
    if (lim < 4) { return; }
    os << "4" << std::endl;
    if (lim < 5) { return; }
    os << "bizz" << std::endl;
    if (lim < 6) { return; }
    os << "fuzz" << std::endl;

    int next3 = 9;
    int next5 = 10;

    for (int num = 7; num <= lim; ++num)
    {
        bool div3 = (num == next3);
        bool div5 = (num == next5);
        if (div3 && div5) {
            os << "fuzzbizz" << std::endl;
            next3 = num+3;
            next5 = num+5;
        } else if (div3) {
            os << "fuzz" << std::endl;
            next3 = num+3;
        } else if (div5) {
            os << "bizz" << std::endl;
            next5 = num+5;
        } else {
            os << num << std::endl;
        }
    }
}


void fuzzbizz(std::ostream& os, const int lim)
{
    os << "div" << std::endl;
    for (int num = 1; num <= lim; ++ num)
    {
        bool div3 = ((num % 3) == 0);
        bool div5 = ((num % 5) == 0);

        if (div3 && div5) {
            os << "fuzzbizz" << std::endl;
        } else if (div3) {
            os << "fuzz" << std::endl;
        } else if (div5) {
            os << "bizz" << std::endl;
        } else {
            os << num << std::endl;
        }
    }
}

int main(int argc, char** argv)
{

    if (argc > 1)
    {
        std::cout << "running inc version" << std::endl;
        for (int i = 0; i < ITER; ++i)
        {
            std::ostringstream os;
            fuzzbizz_inc(os, MAX_NUM);
        }
    }
    else
    {
        std::cout << "running div version" << std::endl;
        for (int i = 0; i < ITER; ++i)
        {
            std::ostringstream os;
            fuzzbizz(os, MAX_NUM);
        }
    }

    // std::cout << os.str() << std::endl;

    return 0;
}

// g++ -Wall -Wextra -pedantic -o fuzzbizz fuzzbizz.cpp
