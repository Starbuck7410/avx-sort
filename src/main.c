#include <stdio.h>
// #include "test.h"
#include <immintrin.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define N 10000


uint64_t nanos()
{
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return (uint64_t) ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

int32_t * create_rand_arr(size_t n){
    int32_t * array = (int32_t * ) malloc(n * sizeof(int32_t));
    for(int i = 0; i < n; i++){
        srand(time(NULL) + i);
        int random = rand() % n;
        array[i] = random;
    }
    return array;
}

int32_t * bubble_sort(int32_t * array, size_t n){
    int32_t * r_array = (int32_t * ) malloc(n * sizeof(int32_t));
    memcpy(r_array, array, n * sizeof(int32_t));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(r_array[j] > r_array[j+1]){
                int32_t tmp = r_array[j];
                r_array[j] = r_array[j+1];
                r_array[j+1] = tmp;
            }
        }
    }

    return r_array;
}

__m256i * simd_create_rand_arr(size_t n){
    __m256i * array = (__m256i * ) aligned_alloc(32, n * sizeof(__m256i));
    for(int i = 0; i < n; i++){
        int32_t random[8];
        for(int j = 0; j < 8; j++){
            srand(time(NULL) + i);
            random[j] = rand() % n;
        }
        
        array[i] = _mm256_set_epi32(random[0], random[1], random[2], random[3], random[4], random[5], random[6], random[7]);
    }
    return array;
}

__m256i * simd_bubble_sort(__m256i * array, size_t n){
    __m256i * r_array = (__m256i * ) aligned_alloc(32, n * sizeof(__m256i));
    memcpy(r_array, array, n * sizeof(__m256i));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            __m256i mask;
            mask = _mm256_cmpgt_epi32(r_array[j], r_array[j+1]);
            __m256i temp = r_array[j];

            __m256i arg_a = __builtin_ia32_andsi256(mask, r_array[j+1]);
            __m256i arg_b = __builtin_ia32_andnotsi256(mask, r_array[j]);
            r_array[j] = _mm256_or_epi32(arg_a, arg_b);

            arg_a = __builtin_ia32_andnotsi256(mask, r_array[j+1]);
            arg_b = __builtin_ia32_andsi256(mask, temp);
            r_array[j+1] = _mm256_or_epi32(arg_a, arg_b);
        }
    }

    return r_array;
}



int main(){
    // print_hey();
    int32_t * array = create_rand_arr(N);
    uint64_t time = nanos();
    int32_t * array_sorted = bubble_sort(array, N);
    time = nanos() - time;
    free(array);
    free(array_sorted);

    printf("\n");
    printf("Time passed: %uns\n", time);
    return 0;
}


