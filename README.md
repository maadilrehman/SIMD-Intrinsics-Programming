# SIMD-Intrinsics-Programming
First test the intrinsics capability, there are several ways to do that.
1. Using tools utilities: Like lscpu, sysctl, cpu-z etc.
2. Analyze within a C++ Program:
   Forexample: cout << __builtin_cpu_supports("avx2") << endl;
   Check testCapa.cpp

# Utilize Intrinsics 
Check 1_usingintrinsics.cpp

# Compile Program by enabling intrinsics
g++ -mavx2 -O2 -march=native 1_usingIntrics.cpp  -o exe

-O2 is an optimization flag in GCC and Clang that enables a set of optimizations to improve code performance without significantly increasing compilation time.

## Optimization Levels in GCC/Clang:
-O0 → No optimizations (default), good for debugging.
-O1 → Basic optimizations, faster code with minimal increase in compile time.
-O2 → More aggressive optimizations, improving speed without excessive code size increase.
-O3 → Includes -O2 plus more optimizations like function inlining and vectorization.
-Ofast → Maximum speed optimizations but may break strict IEEE compliance.
-Os → Optimizes for smaller binary size.
-Og → Optimized for debugging while keeping optimizations that don't interfere with it.
## Why Use -O2?
Enables vectorization (-ftree-vectorize).
Unrolls loops (-funroll-loops).
Performs inline function expansion (-finline-functions).
Eliminates dead code (-fdead-code-elimination).
Does not include risky optimizations like -O3 (which may increase code size).

# Analyze the utilization of SIMD Extensions
objdump exe | grep 'xmm\|ymm\|zmm'

# Analyze Performance
There are several ways to analyze performance. 
you can use tools like perf.

perf stat ./exe
