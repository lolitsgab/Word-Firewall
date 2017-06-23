# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include "hash.h"
# include "ll.h"

static inline int realLength(int l)
{
    return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

hashTable *newHT(uint32_t length, uint32_t salt[])
{
    hashTable* newHT = calloc(1, sizeof(hashTable));
    newHT->l = length;
    for(uint32_t i = 0; i < 4; i++)
    {
        newHT->s[i] = salt[i];
    }
    newHT->h = (listNode**)calloc(length,sizeof(listNode*));
    return newHT;
}

void delHT(hashTable *ht)
{
    for(uint32_t i = 0; i < ht->l; i++)
    {
        delLL(ht->h[i]);
    }
    
    free(ht->h);
    free(ht);
}


listNode *findHT(hashTable *ht,  char *word)
{
    uint32_t hashedword = hash(ht->s, word)%(ht->l);
    return findLL(&(ht->h[hashedword]), word);
}

void insertHT(hashTable *ht,  char* oword,  char *nword)
{
    uint32_t hashedword = hash(ht->s, oword)%(ht->l);
    if(ht->h[hashedword])
    {
        listNode *temp = findLL(&(ht->h[hashedword]), oword);
        if(temp ==  NIL)
        {
            insertLL(&(ht->h[hashedword]), oword, nword);
        }
        else
        {
            insertLL(&temp, oword, nword);
        }
        
    }
    else
    {
        ht->h[hashedword] = newNode(oword, nword);
    }
}

void printHT(hashTable *ht)
{
    for(uint32_t i = 0; i <= ht->l; i++)
    {
        if(ht->h[i])
        {
            printLL(ht->h[i]);
        }
    }
}


uint32_t hash(uint32_t s[],  char *key)
{
    uint32_t output[4] = { 0x0 };
    uint32_t sum       = 0x0;
    int keyL           = strlen(key);
    uint8_t *realKey   = (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t
                                                                     ));
    
    memcpy(realKey, key, keyL);
    
    for (int i = 0; i < realLength(keyL); i += 16)
    {
        AES128_ECB_encrypt((uint8_t *) s, 	        // Salt
                           (uint8_t *) realKey + i,	// Input
                           (uint8_t *) output);	        // Output
        sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
    }
    free(realKey);
    return sum;
}

