#include <stdlib.h>
#include <stdint.h>
#include <immintrin.h>

void simd_bubble_sort(__m256i * array, size_t n);
__m256i * simd_create_rand_arr(size_t n);