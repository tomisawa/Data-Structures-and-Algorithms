//
//  main.c
//  DAS01
//
//  Created by 冨澤眞樹 on 2019/09/09.
//  Copyright © 2019 Masaki Tomisawa. All rights reserved.
//

#include "keisoku.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define N_DATA 100000

int  Initb(int b[])
{
    for (int i = 1; i < N_DATA + 1; i++) {
        b[i] = 100;
    }
    int k = rand() % N_DATA + 1;
    b[k] = 95;
    return k;
}

int algorithm0102(int b[], int n)
{
    for (int i = 1; i < n; i++) {
        if (b[i] == 100) continue;
        else return i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int b[N_DATA + 1], k;

    if (argc != 2) {
        printf("Usage %s N \n", argv[0]);
        return 1;
    }
  
    int lcnt = atoi(argv[1]);

//    PrintClockRes();

    srand((unsigned int)time(NULL));

    for (int i = 0; i < lcnt; i++) {
        k = Initb(b);
        StartClock();
        k = algorithm0102(b, N_DATA);
        StopClock();
        printf("%d,", k);
        double Span = CalcClockSpan();
        printf("%f\n", Span);
    }
  
    return 0;
}
