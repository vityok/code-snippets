/// experimenting with std::visitor look-a-like for custom classes

// clang-format off
/// build:
/// g++ -std=c++11 -Wall -Wextra -Wpedantic -pedantic -o visitor visitor.cpp
///
/// g++ -std=c++11 -Wall -Wextra -Wpedantic -pedantic -DUSE_CT -I/mnt/d/work/repos/boost/boost_1_71_0 -o visitor visitor.cpp
///
///
// clang-format on

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define UNUSED(x) (void)(x)

struct Animal
{
    static const int ID = 1;

    virtual ~Animal() = default;
    virtual std::string Name() { return "Animal"; };
    virtual int GetId() const { return ID; };
};

#include "visitor.hpp"

struct Dog : Animal
{
    static const int ID = 2;

    std::string Name() override { return "Dog"; };
    int GetId() const override { return ID; };
};

struct Cat : Animal
{
    static const int ID = 3;
    std::string Name() override { return "Cat"; };
    int GetId() const override { return ID; };
};

struct Lion : Cat
{
    static const int ID = 4;
    std::string Name() override { return "Lion"; };
    int GetId() const override { return ID; };
};

#ifdef USE_CT
/// demo pattern matching a-la JavaScript or some other similar
/// language. Dispatcher function is constructed and immediately applied to the
/// given argument.
void demo(Animal *animal)
{
    return dispatch_([](Dog &a) { std::cout << "Dog? " << a.Name() << std::endl; },

                     [](Lion &a) { std::cout << "Lion? " << a.Name() << std::endl; })(animal);
}
#endif

int main(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    std::vector<std::unique_ptr<Animal>> animals;

    animals.emplace_back(new Animal());
    animals.emplace_back(new Dog());
    animals.emplace_back(new Cat());
    animals.emplace_back(new Lion());

    auto cat = [](Cat &a) { std::cout << "Cat? " << a.Name() << std::endl; };

#ifdef USE_CT
    std::cout << "Using boost::callable_traits" << std::endl;
    // with boost::callable_traits, which were added in boost-1.66. This lets us
    // extract parameter types directly from lambdas.
    const auto dispatch = dispatch_(
        cat,

        [](Dog &a) { std::cout << "Dog? " << a.Name() << std::endl; },

        [](Lion &a) { std::cout << "Lion? " << a.Name() << std::endl; });

    demo(animals[1].get());
#else
    std::cout << "Using standard library only" << std::endl;
    // without boost::callable_types we rely on classes being explicitly listed
    // using animal_kinds struct template instantiation
    //
    // here, despite handler function for Cat is passed, it will not be called
    // because Cat is not listed among accepted types, unlike in the example
    // above, where this list is constructed on the fly from actual function
    // types
    const auto dispatch = make_dispatch(
        animal_kinds<Dog, Lion>{}, cat,
        [](Dog &a) { std::cout << "Dog? " << a.Name() << std::endl; },

        [](Lion &a) { std::cout << "Lion? " << a.Name() << std::endl; });
#endif

    for (auto &animal : animals)
    {
        dispatch(animal.get());
    }

    return 0;
}
