//
//  ll.c
//  Asignment3
//
//  Created by apple on 5/18/17.
//  Copyright © 2017 apple. All rights reserved.
//
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "ll.h"

double fllCalls = 0;
int seeks = 0;

listNode *newNode(char *ospeak , char *nspeak)
{
    listNode *nNode = calloc(1, sizeof(listNode));
    nNode->newspeak = nspeak;
    nNode->oldspeak = ospeak;
    nNode->next = NIL;
    return nNode;
}

void delNode(listNode* node)
{
    free(node -> newspeak);
    free(node -> oldspeak);
    free(node);
}

void delLL(listNode* list)
{
    while(list->next != NIL)
    {
        listNode *temp = list;
        list = list->next;
        delNode(temp);
    }
}

listNode* insertLL(listNode** node,  char* ospeak, char* nspeak)
{
    listNode *nNode = newNode(ospeak, nspeak);
    nNode->next = (*node)->next;
    (*node)->next = nNode;
    //printf("%s %s\n", ospeak, nNode->oldspeak);
    
    return nNode;
}

listNode *findLL(listNode** list,  char *key)
{
    listNode *lastFind = list[0];
    int foundFlag = 0;
    char *str = NULL;
    int max = 0;
    for (listNode *t = list[0]; t != NIL && max < 50; t = t->next)
    {
        seeks++;
        if(t->oldspeak != NULL)
        {
            if(strcasecmp(t->oldspeak, key) == 0)
            {
                lastFind = t;
                foundFlag = 1;
                if(moveToFront)
                {
                    str = strdup(t->newspeak);
                }
            }
        }
        max++;
    }
    if(moveToFront)
    {
        insertLL(list, key, str);
    }
    seeks -= 50;
    fllCalls++;

    
    return (foundFlag >= 1) ? lastFind : NIL;
}

void printLL(listNode *list)
{
    if(!list)
    {
        return;
    }
    if(list->newspeak == NULL && list->oldspeak == NULL && list->next != NULL)
    {
        list = list->next;
    }
    for (listNode *temp = list; temp != NULL; temp = temp->next)
    {
        printf("%s", temp->oldspeak);
        if(temp->newspeak != NULL)
        {
            printf(" -> %s\n", temp->newspeak);
        }
        else
        {
            printf("\n");
        }
    }
    return;

}
