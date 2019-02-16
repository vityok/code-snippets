// TODO work in progress

#include <memory>
#include <vector>
#include <iostream>
#include <iterator>

#include <benchmark/benchmark.h>

using vec_type = std::vector<std::unique_ptr<int>>;

const vec_type::size_type SIZE = 1000;

static void append_pushing(benchmark::State& state)
{
    for (auto _ : state)
    {
	state.PauseTiming(); // Stop timers. They will not count until they are resumed.
	vec_type src;
	vec_type dst;
	benchmark::DoNotOptimize(src.data());
	benchmark::DoNotOptimize(dst.data());

	// create source vector
	for (vec_type::size_type i = 0; i < SIZE; ++i)
	{
	    src.push_back(std::make_unique<int>(i));
	}
	state.ResumeTiming(); // And resume timers. They are now counting again.

	// append it to the destination vector
	for (vec_type::size_type i = 0; i < src.size(); ++i)
	{
	    dst.push_back(std::move(src[i]));
	}

	if (dst.size() != SIZE) { abort(); }
    }
}
BENCHMARK(append_pushing);

static void append_emplacing(benchmark::State& state)
{
    for (auto _ : state)
    {
	state.PauseTiming(); // Stop timers. They will not count until they are resumed.
	vec_type src;
	vec_type dst;
	benchmark::DoNotOptimize(src.data());
	benchmark::DoNotOptimize(dst.data());

	// create source vector
	for (vec_type::size_type i = 0; i < SIZE; ++i)
	{
	    src.emplace_back(std::make_unique<int>(i));
	}
	state.ResumeTiming(); // And resume timers. They are now counting again.

	// append it to the destination vector
	for (vec_type::size_type i = 0; i < src.size(); ++i)
	{
	    dst.emplace_back(std::move(src[i]));
	}

	if (dst.size() != SIZE) { abort(); }
    }
}
BENCHMARK(append_emplacing);

static void append_moving(benchmark::State& state)
{
    for (auto _ : state)
    {
	state.PauseTiming(); // Stop timers. They will not count until they are resumed.
	vec_type src;
	vec_type dst;
	src.reserve(SIZE+1);
	dst.reserve(SIZE+1);
	benchmark::DoNotOptimize(src.data());
	benchmark::DoNotOptimize(dst.data());
	// create source vector
	for (vec_type::size_type i = 0; i < SIZE; ++i)
	{
	    src.push_back(std::make_unique<int>(i));
	}
	state.ResumeTiming(); // And resume timers. They are now counting again.

	// append it to the destination vector
	std::move(std::begin(src), std::end(src), std::back_inserter(dst));

	if (dst.size() != SIZE) { abort(); }
    }
}
BENCHMARK(append_moving);

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

// g++ $(< build.gcc.opt)
// clang -o ptrvec -std=c++14 ptrvec.cpp

