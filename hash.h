# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef _HASH_H
# define _HASH_H
# include <stdint.h>
# include "ll.h"
# include "bf.h"
# include "aes.h"
typedef struct hashTable hashTable;

struct hashTable
{
    uint32_t s[4]; // Salt
    uint32_t l;    // Length
    listNode **h;  // Array of pointers to linked lists
};

hashTable *newHT(uint32_t, uint32_t []);

void delHT(hashTable *);

listNode *findHT(hashTable *,  char *);

void insertHT(hashTable *,  char *,  char *);

uint32_t hash(uint32_t s[],  char *key);

void printHT( hashTable *);
# endif
