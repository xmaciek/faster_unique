# faster_unique
optimized std::unique into warp speed

TL;DR;
A random idea for optimization I had, if you have a range that consists of about 30% duplicates (or more), this will work faster than std::unique (as of gcc 14.2.1, linux)

The algorithm differs from std::unique - where it does not check for consecutive duplicates, but a whole range.
Prereqisite: the range must be sorted.

<img src="https://github.com/xmaciek/faster_unique/blob/main/chart.png"></img>

compiling benchmark
```g++ benchmark_faster_unique.cpp -std=c++20 -lbenchmark -o bench```

compiling test
```g++ test_faster_unique.cpp -std=c++20 -lgtest -lgtest_main -o test```

