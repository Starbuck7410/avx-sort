#include <stdio.h>
// #include "test.h"
#include <immintrin.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define N 2500


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
            srand(time(NULL) + i + j);
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

            __m256i arg_a = _mm256_and_si256(mask, r_array[j+1]);
            __m256i arg_b = _mm256_andnot_si256(mask, r_array[j]);
            r_array[j] = _mm256_or_si256(arg_a, arg_b);

            arg_a = _mm256_andnot_si256(mask, r_array[j+1]);
            arg_b = _mm256_and_si256(mask, temp);
            r_array[j+1] = _mm256_or_si256(arg_a, arg_b);
        }
    }

    return r_array;
}

// int32_t * simd_merge_sorted(__m256i * array, size_t n){
//     int32_t * merged = (int32_t * ) malloc(8 * n * sizeof(int32_t));

//     for(int i = 0; i < n; i++){
//         _mm256_storeu_si256((__m256i * ) merged[8 * i], array[i]);
//     }
//     return merged;

// }


int main(){
    // print_hey();
    __m256i * array = simd_create_rand_arr(N);
    // int32_t * array_sorted = bubble_sort(array, N);
    
    
    uint64_t time = nanos();
    __m256i * array_sorted = simd_bubble_sort(array, N);
    time = nanos() - time;
    
    // int32_t * int_array = simd_merge_sorted(array_sorted, N);

    // for(int i = 0; i < 8 * N; i++){
    //     printf("%d, ", int_array[i]);
    // }


    free(array);
    free(array_sorted);
    // free(int_array);
    printf("\n");
    printf("Sorted %d items in %uns (%ums) \n", N * 8, time, time / 1000000);
    return 0;
}


