//
//  stack1k.c
//  DA
//
//  Created by 冨澤眞樹 on 2019/10/02.
//  Copyright © 2019 Masaki Tomisawa. All rights reserved.
//

#include "stack1k.h"
#define SIZE 1024

static int stack[SIZE + 1], sp = 0;
void push(int);
int  pop(void), empty(void), full(void);

void  init(void)
{
    sp = 0;
}

int empty(void)
{
    return sp;
}

int full(void)
{
    return sp == SIZE;
}

void push(int x)
{
    stack[sp] = x;
    sp++;
    return;
}

int pop()
{
    sp--;
    return stack[sp];
}
