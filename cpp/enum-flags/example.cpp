#include <iostream>

#include "enum-flags.hpp"

enum class Color
{
    None = 0x00,
    Red = 0x01,
    Green = 0x02,
    Blue = 0x04,
    Black = 0x8
};

int main() {
    EnumeratedFlags<Color> pixel;
    pixel += Color::Red;

    EnumeratedFlags<Color> white{Color::Red, Color::Green, Color::Blue};

    std::cout << "white 1?: " << white.AnyOf(Color::Red, Color::Green) << std::endl;
    std::cout << "white 1?: " << white.AllOf(Color::Red, Color::Green, Color::Blue) << std::endl;
    std::cout << "pixel is white?: " << (white == pixel) << std::endl;
    std::cout << "white is RGB?: " << white.SameAs({Color::Red, Color::Green, Color::Blue}) << std::endl;

    std::cout << "pixel.mask = " << pixel.mask << std::endl;
    std::cout << "white.mask = " << white.mask << std::endl;
    
    return 0;
}

// g++ -std=c++17 -Wall -pedantic -o example example.cpp
