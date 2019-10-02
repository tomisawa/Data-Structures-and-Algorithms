//
//  keisoku.c
//  DAS01
//
//  Created by 冨澤眞樹 on 2019/09/10.
//  Copyright © 2019 Masaki Tomisawa. All rights reserved.
//

#include "keisoku.h"
#include <time.h>
#include <stdio.h>

static struct timespec res,t1,t2;
static long sec,nsec;

int  PrintClockRes(void)
{
  if(clock_getres(CLOCK_MONOTONIC,&res) < 0){
    perror("clock_getres");
    return -1;
  }
  printf("Time Precision:\t%ld.%09ld\n", (long)res.tv_sec, res.tv_nsec);
  return 0;
}

int StartClock(void)
{
  if(clock_gettime(CLOCK_MONOTONIC,&t1) < 0){
    perror("clock_gettime begin");
    return -1;
  }
  return 0;
}

int StopClock(void)
{
  if(clock_gettime(CLOCK_MONOTONIC,&t2) < 0){
    perror("clock_gettime end");
    return -1;
  }
  return 0;
}

int PrintClockSpan(void)
{
  sec = t2.tv_sec - t1.tv_sec;
  nsec = t2.tv_nsec - t1.tv_nsec;
  if(nsec < 0){
    sec--;
    nsec += 1000000000L;
  }
  printf("Time Span:\t%ld.%09ld\n",sec,nsec);
  return 0;
}

double CalcClockSpan(void)
{
  sec = t2.tv_sec - t1.tv_sec;
  nsec = t2.tv_nsec - t1.tv_nsec;
  if(nsec < 0){
    sec--;
    nsec += 1000000000L;
  }
  return sec+nsec*1E-9;
}
