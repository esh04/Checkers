#ifndef __QUE_H
#define __QUE_H

// ************This file contains the Queue Implementation in C************

#include "constants.h"
#include "checkers.h"

typedef struct quecontents *Que;
struct quecontents
{
    coordinates c1;
    coordinates c2;
    char c;
    Que next;
};

struct queue
{
    Que front;
    Que rear;
};

typedef struct queue *Queue;

Que newmove(coordinates a, coordinates b, char c);
Queue createQueue();
void enQueue(Queue q, coordinates a, coordinates b, char c);
Que deQueue(Queue q);
void pull(Queue q);
void Reviewgame(Queue q, int n);

#endif
