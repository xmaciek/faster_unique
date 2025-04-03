// MIT License
//
// Copyright (c) Maciej Latocha ( latocha.maciek@gmail.com )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "faster_unique.hpp"

#include <benchmark/benchmark.h>
#include <numeric>
#include <vector>
#include <random>

// ================================================================

class Uniques : public benchmark::Fixture {
public:
    std::vector<uint32_t> data;

    void SetUp( ::benchmark::State& state )
    {
        data.resize( 1'000'000 );
        benchmark::DoNotOptimize( data.data() );
        std::ranges::generate( data, [r=std::mt19937(std::random_device()()), m=state.range( 0 )]() mutable { return r() % m; } );
        std::ranges::sort( data );
    }
    void TearDown( ::benchmark::State& ) {}
};

BENCHMARK_DEFINE_F(Uniques, faster_unique)( benchmark::State& state )
{
    for ( auto _ : state ) {
        [[maybe_unused]]
        std::vector<uint32_t>::iterator it;
        benchmark::DoNotOptimize( it = faster_unique( data.begin(), data.end() ) );
    }
}

BENCHMARK_REGISTER_F(Uniques, faster_unique)
    ->Arg(16)
    ->Arg(200)
    ->Arg(500)
    ->Arg(1'000)
    ->Arg(2'000)
    ->Arg(5'000)
    ->Arg(8'000)
    ->Arg(15'000)
    ->Arg(20'480)
    ->Arg(50'000)
    ->Arg(80'000)
    ->Arg(120'000)
    ->Arg(180'000)
    ->Arg(200'000)
    ->Arg(300'000)
    ->Arg(350'000)
    ->Arg(400'000)
    ->Arg(450'000)
    ->Arg(500'000)
    ->Arg(550'000)
    ->Arg(600'000)
    ->Arg(630'000)
    ->Arg(665'000)
    ->Arg(700'000)
    ->Arg(725'000)
    ->Arg(750'000)
    ->Arg(775'000)
    ->Arg(800'000)
    ->Arg(850'000)
    ->Arg(900'000)
    ->Arg(950'000)
    ;

BENCHMARK_DEFINE_F(Uniques, std_unique)( benchmark::State& state )
{
    for ( auto _ : state ) {
        [[maybe_unused]]
        std::vector<uint32_t>::iterator it;
        benchmark::DoNotOptimize( it = std::unique( data.begin(), data.end() ) );
    }
}

BENCHMARK_REGISTER_F(Uniques, std_unique)
    ->Arg(16)
    ->Arg(200)
    ->Arg(500)
    ->Arg(1'000)
    ->Arg(2'000)
    ->Arg(5'000)
    ->Arg(8'000)
    ->Arg(15'000)
    ->Arg(20'480)
    ->Arg(50'000)
    ->Arg(80'000)
    ->Arg(120'000)
    ->Arg(180'000)
    ->Arg(200'000)
    ->Arg(300'000)
    ->Arg(350'000)
    ->Arg(400'000)
    ->Arg(450'000)
    ->Arg(500'000)
    ->Arg(550'000)
    ->Arg(600'000)
    ->Arg(630'000)
    ->Arg(665'000)
    ->Arg(700'000)
    ->Arg(725'000)
    ->Arg(750'000)
    ->Arg(775'000)
    ->Arg(800'000)
    ->Arg(850'000)
    ->Arg(900'000)
    ->Arg(950'000)
    ;

// ================================================================

class NoUniques : public benchmark::Fixture {
public:
    std::vector<uint32_t> data;

    void SetUp( ::benchmark::State& )
    {
        data.resize( 1'000'000 );
        benchmark::DoNotOptimize( data.data() );
        std::iota( data.begin(), data.end(), 0u );
    }
    void TearDown( ::benchmark::State& ) {}
};

BENCHMARK_F(NoUniques, faster_unique)( benchmark::State& state )
{
    for ( auto _ : state ) {
        [[maybe_unused]]
        auto it = faster_unique( data.begin(), data.end() );
    }
}

BENCHMARK_F(NoUniques, std_unique)( benchmark::State& state )
{
    for ( auto _ : state ) {
        [[maybe_unused]]
        auto it = std::unique( data.begin(), data.end() );
    }
}

// ================================================================

BENCHMARK_MAIN();
