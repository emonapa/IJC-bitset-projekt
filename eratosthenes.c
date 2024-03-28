 /*
-------------------------------------------------------------
    eratosthenes.c
    Solution to IJC-DU1, example A)
    Date: 14.3.2024
    Author: Václav Matyáš, FIT
    Compiler: gcc 11.4.0
    Description: Filters primes in bit array
-------------------------------------------------------------
*/

#include "eratosthenes.h"
#include <math.h>

#ifdef USE_INLINE
extern void bitset_free(bitset_t bitArray);
extern bitset_index_t bitset_size(bitset_t bitArray);
extern void bitset_setbit(bitset_t bitArray, bitset_index_t index, int isTrue);
extern int bitset_getbit(bitset_t bitArray, bitset_index_t index);
#endif

void Eratosthenes(bitset_t bitArray) {
    bitset_index_t size = bitset_size(bitArray);
    bitset_index_t limit = sqrt(size);
    
    for (bitset_index_t i = 2; i <= limit; i++) {
        if (!bitset_getbit(bitArray, i)) {
            // Setting the multiples of the current prime to 1
            for (bitset_index_t j = i*i; j < size; j += i) {
                bitset_setbit(bitArray, j, 1);
            }
        }
    }
}
