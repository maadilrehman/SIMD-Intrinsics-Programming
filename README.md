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

# Analyze the utilization of SIMD Extensions
objdump exe | grep 'xmm\|ymm\|zmm'

# Analyze Performance
There are several ways to analyze performance. 
you can use tools like perf.
perf stat ./exe
