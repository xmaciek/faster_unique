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

#include <gtest/gtest.h>

#include <vector>
#include <random>

TEST( FasterUnique, doesItWork )
{
    std::vector<uint32_t> data( 1000 );
    std::ranges::generate( data, [r=std::mt19937(1)]() mutable { return r() % 16; } );
    std::ranges::sort( data );
    std::vector<uint32_t> data2 = data;
    data.erase( std::unique( data.begin(), data.end() ), data.end() );
    data2.erase( faster_unique( data2.begin(), data2.end() ), data2.end() );
    EXPECT_EQ( data, data2 );
}
