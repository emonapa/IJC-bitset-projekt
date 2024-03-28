 /*
-------------------------------------------------------------
    primes.c
    Solution to IJC-DU1, example A)
    Date: 14.3.2024
    Author: Václav Matyáš, FIT
    Compiler: gcc 11.4.0
    Description: Usage example for bit array and 
                 eratosthenes function.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <time.h>
#include "eratosthenes.h"

#define LIMIT 666000000
#define SHOW_LIMIT 10

void show_primes(bitset_t pole, int show_limit) {
    bitset_index_t primes_last[show_limit];
    bitset_index_t j = 0;
    for (bitset_index_t i = bitset_size(pole)-1; i > 0 && j < SHOW_LIMIT; i--) {
        if (!bitset_getbit(pole, i)) {
            primes_last[j] = i;
            j++;
        }
    }

    for (int i = show_limit-1; i >= 0; i--) {
        printf("%ld\n", primes_last[i]);
    }
}

int main() {
    clock_t start = clock();
    bitset_alloc(nums_all, LIMIT);

    Eratosthenes(nums_all);

    show_primes(nums_all, SHOW_LIMIT);

    bitset_free(nums_all);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}