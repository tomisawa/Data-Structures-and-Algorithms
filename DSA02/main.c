//
//  main.c
//  DSA02 stack
//
//  Created by 冨澤眞樹 on 2019/10/02.
//  Copyright © 2019 Masaki Tomisawa. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include "stack1k.h"
#define MAXLN 1000
int calc(char *), number(char **);

int  main(void)
{
    char in[MAXLN];
    while (1) {
        printf("\nInput Exp :");
        fgets(in, MAXLN, stdin);
        printf("Calc = %d\n", calc(in));
    }
}

int calc(char *p)
{
    int temp;
    while ((*p != '\0' && *p != '\n')) {
        switch (*p) {
            case ' ': break;
            case '+':
                temp = pop();
                push(pop() + temp);
                break;
            case '-':
                temp = pop();
                push(pop() - temp);
                break;
            case '*':
                temp = pop();
                push(pop() * temp);
                break;
            case '/':
                temp = pop();
                push(pop() / temp);
                break;
            default: push(number(&p));
        }
        p++;
    }
    return pop();
}

int number(char **p)
{
    int n;
    n = 0;
    do {
        n = n * 10 + **p - '0';
        (*p)++;
    } while (isdigit(**p));
    (*p)--;
    return n;
}
