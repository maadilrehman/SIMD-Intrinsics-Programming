#pragma GCC target("avx2")
#pragma GCC optimize("O2")

#include <x86intrin.h> // All intrinsics
#include <bits/stdc++.h> // Selective
#include <immintrin.h>
#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace std;

// Serial version of element-wise addition
void serial_add(const float* a, const float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

// AVX-optimized version using 256-bit SIMD
void avx_add(const float* a, const float* b, float* result, int size) {
    int i;
    for (i = 0; i <= size - 8; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);  // Use aligned load
        __m256 vb = _mm256_load_ps(&b[i]);
        __m256 vres = _mm256_add_ps(va, vb);
        _mm256_store_ps(&result[i], vres);
    }
    // Process remaining elements
    for (; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

// Function to measure execution time
template <typename Func>
double measure_time(Func function, const float* a, const float* b, float* result, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    function(a, b, result, size);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count(); // Return time in milliseconds
}

int main() {
    constexpr int size = 10000000; // Large array size (10 million elements)

    // Allocate 32-byte aligned arrays
    alignas(32) static float a[size];
    alignas(32) static float b[size];
    alignas(32) static float result[size];

    // Initialize arrays with random values
    for (int i = 0; i < size; i++) {
        a[i] = static_cast<float>(rand()) / RAND_MAX;
        b[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // Measure serial execution time
    double serial_time = measure_time(serial_add, a, b, result, size);
    std::cout << "Serial execution time: " << serial_time << " ms\n";

    // Measure AVX execution time
    double avx_time = measure_time(avx_add, a, b, result, size);
    std::cout << "AVX execution time: " << avx_time << " ms\n";

    // Compute speedup
    std::cout << "Speedup: " << serial_time / avx_time << "x\n";

    return 0;
}

