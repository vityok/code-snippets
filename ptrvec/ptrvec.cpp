// TODO work in progress

#include <memory>
#include <vector>
#include <iostream>
#include <iterator>

#include <benchmark/benchmark.h>

struct Point
{
    int _x;
    int _y;

    Point(int x, int y) : _x{x}, _y{y} {}
};

using vec_ptr_type = std::vector<std::unique_ptr<Point>>;
using vec_str_type = std::vector<Point>;

const vec_ptr_type::size_type SIZE_PTR = 1000;
const vec_str_type::size_type SIZE_STR = 1000;

static void append_pushing(benchmark::State& state)
{
    for (auto _ : state)
    {
        vec_ptr_type src;
        vec_ptr_type dst;
        benchmark::DoNotOptimize(src.data());
        benchmark::DoNotOptimize(dst.data());

        // create source vector
        for (vec_ptr_type::size_type i = 0; i < SIZE_PTR; ++i)
        {
            src.push_back(std::make_unique<Point>(i, SIZE_PTR-i));
        }

        // append it to the destination vector
        for (vec_ptr_type::size_type i = 0; i < src.size(); ++i)
        {
            dst.push_back(std::move(src[i]));
        }

        if (dst.size() != SIZE_PTR) { abort(); }
    }
}
BENCHMARK(append_pushing);

static void append_emplacing_ptr(benchmark::State& state)
{
    for (auto _ : state)
    {
        vec_ptr_type src;
        vec_ptr_type dst;
        benchmark::DoNotOptimize(src.data());
        benchmark::DoNotOptimize(dst.data());

        // create source vector
        for (vec_ptr_type::size_type i = 0; i < SIZE_PTR; ++i)
        {
            src.emplace_back(std::make_unique<Point>(i, SIZE_PTR-i));
        }

        // append it to the destination vector
        for (vec_ptr_type::size_type i = 0; i < src.size(); ++i)
        {
            dst.emplace_back(std::move(src[i]));
        }

        if (dst.size() != SIZE_PTR) { abort(); }
    }
}
BENCHMARK(append_emplacing_ptr);

static void append_moving_ptr(benchmark::State& state)
{
    for (auto _ : state)
    {
        vec_ptr_type src;
        vec_ptr_type dst;
        src.reserve(SIZE_PTR+1);
        dst.reserve(SIZE_PTR+1);
        benchmark::DoNotOptimize(src.data());
        benchmark::DoNotOptimize(dst.data());

        // create source vector
        for (vec_ptr_type::size_type i = 0; i < SIZE_PTR; ++i)
        {
            src.push_back(std::make_unique<Point>(i, SIZE_PTR-i));
        }

        // append it to the destination vector
        std::move(std::begin(src), std::end(src),
                  std::back_inserter(dst));

        benchmark::ClobberMemory(); // Force data to be written to memory.

        if (dst.size() != SIZE_PTR) { abort(); }
    }
}
BENCHMARK(append_moving_ptr);

static void append_moving_str(benchmark::State& state)
{
    for (auto _ : state)
    {
        vec_str_type src;
        vec_str_type dst;
        src.reserve(SIZE_STR+1);
        dst.reserve(SIZE_STR+1);
        benchmark::DoNotOptimize(src.data());
        benchmark::DoNotOptimize(dst.data());

        // create source vector
        for (vec_str_type::size_type i = 0; i < SIZE_STR; ++i)
        {
            src.emplace_back(i, SIZE_STR-i);
            benchmark::ClobberMemory(); // Force data to be written to memory.
        }

        // append it to the destination vector
        std::move(std::begin(src), std::end(src),
                  std::back_inserter(dst));

        benchmark::ClobberMemory(); // Force data to be written to memory.

        if (dst.size() != SIZE_STR) { abort(); }
    }
}
BENCHMARK(append_moving_str);

BENCHMARK_MAIN();
/*
int main()
{
    append_pushing();
    append_emplacing();
    append_moving();

    return 0;
}
*/

// How to compile and run:
//
// g++ $(< build.gcc.opt)
// ./ptrvec  --benchmark_repetitions=10 --benchmark_report_aggregates_only=true
//
// clang -o ptrvec -std=c++14 ptrvec.cpp
