#include <stdlib.h>
#include <stdint.h>
#include <immintrin.h>
#include <time.h>
#include <string.h>

__m256i * simd_create_rand_arr(size_t n){
    __m256i * array = (__m256i * ) aligned_alloc(32, n * sizeof(__m256i));
    for(int i = 0; i < n; i++){
        int32_t random[8];
        for(int j = 0; j < 8; j++){
            srand(time(NULL) + 70*i + 701*j);
            random[j] = rand() % (8*n);
        }
        
        array[i] = _mm256_set_epi32(random[0], random[1], random[2], random[3], random[4], random[5], random[6], random[7]);
    }
    return array;
}

void simd_bubble_sort(__m256i * array, size_t n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            __m256i mask;
            mask = _mm256_cmpgt_epi32(array[j], array[j+1]);
            __m256i temp = array[j];

            array[j] = _mm256_or_si256(_mm256_and_si256(mask, array[j+1]), _mm256_andnot_si256(mask, array[j]));

            array[j+1] = _mm256_or_si256(_mm256_andnot_si256(mask, array[j+1]), _mm256_and_si256(mask, temp));
        }
    }

    int32_t * int_array = (int32_t * ) malloc(8 * n * sizeof(int32_t));
    int32_t * merged = (int32_t * ) array;
    size_t  offsets[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    for(int i = 0; i < (8 * n); i++){
        int max_index = -1;
        for(int j = 0; j < 8; j++){
            if(max_index == -1 && offsets[j] != -1){
                max_index = j;
            }
            if(max_index != -1 && offsets[j] != -1){
                max_index = (merged[offsets[max_index]] > merged[offsets[j]]) ? j : max_index;
            }
        }

        int_array[i] = merged[offsets[max_index]];
        if((offsets[max_index] += 8) >= (8 * n)){
            offsets[max_index] = -1;
        }
    }

    memcpy(array, int_array, 8 * n * sizeof(int32_t));
    free(int_array);
}