#include <stdio.h>
#include "sort.h"
#include "simd_sort.h"
#include <immintrin.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>


#define N 1000


uint64_t nanos(){
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return (uint64_t) ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}


int main(){

    __m256i * simd_array = simd_create_rand_arr(N);
    int32_t * int_array = create_rand_arr(8*N);


    int32_t * int_array_sorted = (int32_t * ) malloc(8 * N * sizeof(int32_t));
    memcpy(int_array_sorted, int_array, 8 * N * sizeof(int32_t));

    uint64_t int_time = nanos();
    bubble_sort(int_array_sorted, 8 * N);
    int_time = nanos() - int_time;


    __m256i * simd_array_sorted = (__m256i * ) aligned_alloc(32, N * sizeof(__m256i));
    memcpy(simd_array_sorted, simd_array, N * sizeof(__m256i));

    uint64_t simd_time = nanos();
    simd_bubble_sort(simd_array_sorted, N);
    simd_time = nanos() - simd_time;



    free(int_array);
    free(int_array_sorted);
    free(simd_array);
    free(simd_array_sorted);

    printf("\n");
    printf("Regular sort | Sorted %d items in %uns (%ums) \n", N * 8, int_time, int_time / 1000000);
    printf("SIMD sort    | Sorted %d items in %uns (%ums) \n", N * 8, simd_time, simd_time / 1000000);
    printf("Ratio        | %.2f times faster!\n", ((double) int_time) / simd_time);
    return 0;
}


