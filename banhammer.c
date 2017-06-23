//
//  main.c
//  Asignment3
//
//  Created by apple on 5/17/17.
//  Copyright © 2017 apple. All rights reserved.
//

# include <stdio.h>
# include <math.h>
# include "bf.h"
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include "ll.h"
bool moveToFront;
int report(bloomF *bf, bloomF *bf2, hashTable *ht, listNode *Rep, listNode *noRep, char *word);
void printStatement(int pStats, listNode *noRep, listNode *Rep);
int yylex(void);
extern char* yytext;
extern FILE* yyin;
int lineCount(void);
int wordCount(void);
int flexCount(void);
int joyCamp = 0;
int rethink = 0;
double average = 0;
int dict = 0;
int trans = 0;
int text = 0;
int main(int argc, char * argv[])
{
    moveToFront = false;
    
    uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // First Bloom filter
    uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // SecondBloom filter
    uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; // Hash table
    uint32_t size = (uint32_t) pow(2, 20);
    uint32_t sizeHT = (uint32_t) 1000;
    char* copy = NULL;
    char* tmp1 = NULL;
    char* tmp2 = NULL;
    char *ovoWord = (char*) malloc(sizeof(char)*100);
    char *novaWord = (char*) malloc(sizeof(char)*100);
    int pStats = 0;
    //moveToFront = false;
    int option;
    bloomF *bf = newBF(size, initA);
    bloomF *bf2 = newBF(size, initB);
    hashTable *ht = newHT(sizeHT, initH);
    listNode *Rep = newNode(NULL, NULL);
    listNode *noRep = newNode(NULL, NULL);
    int mtf = 0;
    opterr = 0;
    
    while ((option = getopt (argc , argv , " sf:h:mb") ) != -1)
    {
        switch (option)
        {
                /************* print stats supress words **************/
            case 's':
                pStats = 1;
                break;
                /************* size of bloomfilter **************/
            case 'f':
                size = (uint32_t)atoi(optarg);
                break;
                /************* size of hashtable **************/
            case 'h':
                sizeHT = (uint32_t)atoi(optarg);
                break;
                /************* move to front = true **************/
            case 'm':
                mtf = 1;
                break;
                /************* move to front = false **************/
            case 'b':
                moveToFront = false;
                break;
            default:
                fprintf(stderr, "unkown flag or argument where not needed.");
                return 2;
        }
        
    }
    
    //read badspeak into hashtable
    FILE *badspeak = fopen("/afs/cats.ucsc.edu/users/g/darrell/badspeak.txt", "r");
    while(fscanf(badspeak, "%s", ovoWord) == 1)
    {
        tmp1 = strdup(ovoWord);
        //printf("%s\n", tmp1);
        //fflush(stdout);
        insertHT(ht, tmp1, NULL);
        setBF(bf, tmp1);
        setBF(bf2, tmp1);
        dict++;
    }
    fclose(badspeak);
    
    
    /************************** newspeak.txt ***************************/
    /************************** newspeak.txt ***************************/
    /************************** newspeak.txt ***************************/
    /************************** newspeak.txt ***************************/
    FILE *newspeak = fopen("/afs/cats.ucsc.edu/users/g/darrell/newspeak.txt", "r");
    char* oWord = (char*) malloc(sizeof(char)*100);
    char* nWord = (char*) malloc(sizeof(char)*100);
    int p = 0;
    while(fscanf(newspeak, "%s %s", oWord, nWord) == 2)
    {
        tmp1 = strdup(oWord);
        tmp2 = strdup(nWord);
        insertHT(ht, tmp1, tmp2);
        setBF(bf, tmp1);
        setBF(bf2, tmp1);
        p++;
        trans++;
        //printf("%s -> %s\n", oWord, nWord);
    }
    //printf("%d", p);
    fclose(newspeak);
    
    //printHT(ht);
    
    //check user input with bloomfilters
    //FILE *ep = fopen("ep.txt", "r");
    /************************** STDIN ***************************/
    /************************** STDIN ***************************/
    /************************** STDIN ***************************/
    /************************** STDIN ***************************/
    if(mtf == 1)
    {
        moveToFront = true;
    }
    yyin = stdin;
    int tokenID = 0;
    while(tokenID != -1)
    {
        text++;
        tokenID = yylex();
        report(bf, bf2, ht, Rep, noRep, yytext);
        //printf("%s\n", yytext);
    }
    //printHT(ht);
    average = (fllCalls/(double)seeks);
    
    if(pStats==1)
    {
        printf("\nSeeks %d, Average %0.6f, Dictionary %d, Translations %d, Text %d, Densities: %0.6f, %0.6f", seeks, average, dict, trans, text, (double)(dict+trans*1.5)/lenBF(bf), (double)(dict+trans*1.5)/lenBF(bf2));
    }
    else
    {
        printStatement(pStats, noRep, Rep);
    }
    //printLL(Rep);
    free(copy);
    free(tmp1);
    free(tmp2);
    free(oWord);
    free(nWord);
    free(ovoWord);
    free(novaWord);
    
    return 0;
}

void printStatement(int pStats, listNode *noRep, listNode *Rep)
{
    if(pStats == 0)
    {
        if(joyCamp != 0)
        {
            
            printf("Dear Comrade,\n\nYou have chosen to use degenerate words that may cause hurt\nfeelings or cause your comrades to think unpleasant thoughts.\nThis is doubleplus bad. To correct your wrongthink and\nsave community consensus we will be sending you to joycamp\nadministered by Miniluv.\n\n");
            
            
            printf("Your errors:\n\n");
            printLL(noRep);
            if(rethink != 0)
            {
                printf("\nThink on these words during your vacation!\n\n");
                printLL(Rep);
            }
        }
        else if(rethink != 0)
        {
            printf("Dear Comrade,\n\nSubmitting your text helps to preserve feelings and prevent\nbadthink. Some of the words that you used are not goodspeak.\nThe list shows how to turn the oldspeak words into newspeak.\n\n");
            
            printLL(noRep);
        }
    }
    return;
}

int report(bloomF *bf, bloomF *bf2, hashTable *ht, listNode *Rep, listNode *noRep, char *word)
{
    
    //printf("test2");
    //fflush(stdout);
    for(int i = 0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
    }
    char* tmp1 = NULL;
    tmp1 = strdup(word);
    if(findLL(&noRep, tmp1) || findLL(&Rep, tmp1))
    {
        return 1;
    }
    //printf("%s\n", tmp1);
    if(memBF(bf, tmp1))
    {
        //printf("%s\n", tmp1);
        if(memBF(bf2, tmp1))
        {
            //printf("%s\n", tmp1);
            
            if(findHT(ht, tmp1))
            {
                
                
                if((findHT(ht, tmp1))->newspeak == NULL)
                {
                    //printf("oooo0000000000000\n");
                    insertLL(&noRep, tmp1, NULL);
                    joyCamp=1;
                    //printf("%s\n", tmp1);
                }
                else
                {
                    //printf("xxxx\n");
                    insertLL(&Rep, tmp1, (findHT(ht, tmp1))->newspeak);
                    rethink=1;
                    //printf("%s\n", tmp1);
                    
                }
            }
        }
    }
    
    
    return 0;
}



























