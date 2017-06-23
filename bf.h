// bf.h — Bloom filter interface

# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "hash.h"

typedef struct bloomF
{
    uint8_t *v; // BF
    uint32_t l; // Length
    uint32_t s [4]; // Salt
}bloomF ;

uint32_t hashBF (bloomF * tmep, char *);

static inline bloomF *newBF (uint32_t len, uint32_t salt[])
{
    bloomF *bf = calloc(1, sizeof(bloomF)); //allocate space for variable
    bf -> l = len;
    bf -> v = calloc(len/8+1, sizeof(uint8_t)); //allocate space for vector
    for(int i = 0; i < 4; i++)
    {
        bf->s[i] = salt[i];
    }
    return bf;
}

static inline void delBF (bloomF *bf)
{
    free(bf -> v);
    free(bf);
}

static inline uint32_t lenBF (bloomF *x)
{
    return x -> l;
}

static inline uint32_t countBF (bloomF *b)
{
    uint32_t count;
    uint32_t mask = 1;
    for(uint32_t i = 0; i < lenBF(b)/8; i++)
    {
        count += (((b -> v[i/8]) & mask) != 0) ? 1 : 0;
        mask = mask << 1;
    }
    return count;
}


static inline void clrBF (bloomF *x, char * key )
{
    uint32_t bit = hashBF(x, key);
    bit = bit%(lenBF(x));
    x->v[bit/8] &= ~(0x1 << bit%8);
}

static inline uint32_t valBF(bloomF *x, uint32_t k)
{
    k = k%(lenBF(x));
    return ((x->v[k / 8] & (0x1 << k % 8)) != 0);
}

static inline void setBF (bloomF *x, char * key )
{
    uint32_t k = hashBF(x, key);
    k = k%(lenBF(x));
    x->v[k / 8] |=  (0x1 << k % 8);
}

static inline uint32_t memBF (bloomF *x, char * key)
{
    uint32_t bit = hashBF(x, key);
    return valBF(x, bit);
}

static inline void printBF (bloomF *x)
{
    for(uint32_t i = 0; i < lenBF(x); i++)
    {
        printf("%u ", valBF(x, i));
    }
}
# endif
