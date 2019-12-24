#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNTING

static int64_t calculator(int64_t a, int64_t b, int64_t m);

int64_t multimod_p3(int64_t a, int64_t b, int64_t m) {
  clock_t start,finish;
  start=clock();
  
  int64_t ret = 0; 
#ifdef COUNTING
  int64_t a1=a, b1=b, m1=m, res;
  FILE *fp = fopen("../../rand_num","r");
  if(!fp){
    printf("can't open file\n");
    return false;
  }
  
  while(!feof(fp)){
    fscanf(fp,"%ld %ld %ld %ld",&a, &b, &m, &res);
    uint64_t ans = calculator(a,b,m);
    printf("a:%20ld b:%20ld m:%20ld ref_ans:%20ld my_ans:%20ld corectness:%s\n", a, b, m, res, ans, res - ans ? "WRONG" : "RIGHT");
  }
  fclose(fp);
  ret = calculator(a1,b1,m1);
#endif
#ifndef COUNTING
  ret = calculator(a,b,m);
#endif
  finish=clock();
  double duration = (double)(finish-start)/CLOCKS_PER_SEC;
  printf("%f seconds on p2.c and the answer is ",duration);
  return ret;
}

static int64_t calculator(int64_t a, int64_t b, int64_t m){
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}
