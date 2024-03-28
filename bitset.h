 /*
-------------------------------------------------------------
    bitset.h
    Solution to IJC-DU1, example A)
    Date: 14.3.2024
    Author: Václav Matyáš, FIT
    Compiler: gcc 11.4.0
    Description: General macros for bit array.
                 bitset_create is not optimal for
                 large arrays.
-------------------------------------------------------------
*/

#ifndef BITSET_H
#define BITSET_H

#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

extern void error_exit(const char *fmt, ...);
extern void warning_msg(const char *fmt, ...);

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;


#define bits_to_indexT(size) ((size_t)(size) / (sizeof(unsigned long) * CHAR_BIT) + 1 + ((size_t)(size) % (sizeof(unsigned long) * CHAR_BIT) != 0))

#define bitset_create(bitArray, size) \
    static_assert(size > 0);          \
    bitset_index_t bitArray[bits_to_indexT(size)] = {size}

#define bitset_alloc(bitArray, size) \
    assert(size > 0);                                            \
    bitset_t bitArray = calloc(bits_to_indexT(size), sizeof(unsigned long));                    \
    if (bitArray == NULL) { \
        printf("bitset_alloc: Chyba alokace paměti"); \
        return 1; \
    } \
    bitArray[0] = size

#ifndef USE_INLINE

#define bitset_free(bitArray) free(bitArray)

#define bitset_size(bitArray) (bitArray[0])

#define bitset_fill(bitArray, isTrue) \
    memset(&bitArray[1], isTrue ? 0xFF : 0, (bits_to_indexT(bitArray[0])-1)*sizeof(unsigned long))

#define bitset_setbit(bitArray, index, isTrue) do { \
    unsigned long array_position = index / (CHAR_BIT * sizeof(unsigned long)) + 1; \
    if (array_position > bits_to_indexT(bitArray)) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", \
               (unsigned long)index, bitArray[0]); \
    } \
    if (isTrue) \
        bitArray[array_position] |= (1UL << ((index) % (CHAR_BIT * sizeof(unsigned long)))); \
    else \
        bitArray[array_position] &= ~(1UL << ((index) % (CHAR_BIT * sizeof(unsigned long)))); \
    } while(0);

#define bitset_getbit(bitArray, index) ( \
    (index >= bitset_size(bitArray)) ? \
    error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", \
                (unsigned long)index, bitArray[0]), 1 \
    : \
    (int) ((bitArray[(index) / (CHAR_BIT * sizeof(unsigned long)) + 1] >> ((index) % (CHAR_BIT * sizeof(unsigned long)))) & 1) \
    )

#else

inline void bitset_free(bitset_t bitArray) {
    free(bitArray);
}

inline bitset_index_t bitset_size(bitset_t bitArray) {
    return bitArray[0];
}

inline void bitset_fill(bitset_t bitArray, int isTrue) {
    memset(&bitArray[1], isTrue ? 0xFF : 0, (bits_to_indexT(bitArray[0]) - 1) * sizeof(unsigned long));
}

inline void bitset_setbit(bitset_t bitArray, bitset_index_t index, int isTrue) {
    unsigned long array_position = index / (CHAR_BIT * sizeof(unsigned long)) + 1; \
    if (array_position > bits_to_indexT(bitArray)) { 
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", 
               (unsigned long)index, bitArray[0]); 
    } 
    if (isTrue)
        bitArray[array_position] |= (1UL << ((index) % (CHAR_BIT * sizeof(unsigned long))));
    else
        bitArray[array_position] &= ~(1UL << ((index) % (CHAR_BIT * sizeof(unsigned long))));
}

inline int bitset_getbit(bitset_t bitArray, bitset_index_t index) {
    if (index >= bitset_size(bitArray)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, bitArray[0]);
    }
    return (bitArray[(index) / (CHAR_BIT * sizeof(unsigned long)) + 1] >> ((index) % (CHAR_BIT * sizeof(unsigned long)))) & 1;
}

#endif
#endif // BITSET_H
