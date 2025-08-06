#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

int32_t * create_rand_arr(size_t n){
    int32_t * array = (int32_t * ) malloc(n * sizeof(int32_t));
    for(int i = 0; i < n; i++){
        srand(time(NULL) + i);
        int random = rand() % n;
        array[i] = random;
    }
    return array;
}


void bubble_sort(int32_t * array, size_t n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(array[j] > array[j+1]){
                int32_t tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }

}