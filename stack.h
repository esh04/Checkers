#ifndef __STACK_H
#define __STACK_H

#include<stdio.h>

//************This file contains implementation of Stacks in C************

typedef struct StackContents StackContents;

struct StackContents{
    coordinates start;
    coordinates final;
    char turn;
    int cap;
    int type;
};

void push(StackContents s[10000], StackContents c);
void pop(StackContents s[10000]);

#endif
