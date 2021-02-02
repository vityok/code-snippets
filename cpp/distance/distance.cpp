/// perform sanity checks on a string in a buffer. Check whether
/// std::distance results can be used instead of strlen

#include <assert.h>
#include <string.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    auto buff = std::vector<char>{100};

    // empty string
    const auto emptyStringEnd = std::find(buff.begin(), buff.end(), '\0');
    assert(std::distance(buff.begin(), emptyStringEnd) == strlen(buff.data()));

    // normal string
    const std::string msg = "Hello World!";
    std::copy(msg.begin(), msg.end(), std::back_inserter(buff));

    const auto msgStringEnd = std::find(buff.begin(), buff.end(), '\0');
    assert(std::distance(buff.begin(), msgStringEnd) == strlen(buff.data()));

    // buffer is full, end of string is beyond end of buffer, strlen
    // might reach beyond end of allocated buffer and trigger a crash
    std::fill(buff.begin(), buff.end(), 'A');
    const auto badStringEnd = std::find(buff.begin(), buff.end(), '\0');
    assert(badStringEnd == buff.end());

    // now the string is good, with 0 in the last cell
    buff.back() = '\0';

    const auto fullStringEnd = std::find(buff.begin(), buff.end(), '\0');
    assert(std::distance(buff.begin(), fullStringEnd) == strlen(buff.data()));
}

// g++ -g -std=c++14 -o distance distance.cpp
