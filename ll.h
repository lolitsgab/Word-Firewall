# ifndef NIL
# define NIL ( void *) 0
# endif
# ifndef MTF
# define MTF true
# endif

# ifndef _LL_H

# define _LL_H

# include <stdbool.h>

extern bool moveToFront ;
extern int seeks;
extern double fllCalls;

typedef struct listNode listNode ;

struct listNode
{
    char * oldspeak , * newspeak ;
    listNode * next ;
};

listNode * newNode ( char * , char *) ;

void delNode ( listNode *) ;

void delLL ( listNode *) ;

listNode* insertLL(listNode** ,  char* , char* );

listNode * findLL ( listNode ** ,  char *) ;

void printLL ( listNode *) ;
# endif
