#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define bit 63
#define COUNTING

static int64_t calculator(int64_t a, int64_t b, int64_t m);

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
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
    printf("a:%20ld b:%20ld m:%20ld ref_ans:%20ld my_ans:%20ld cor:%s\n", a, b, m, res, ans, res - ans ? "WRONG" : "RIGHT");
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
  /*uint64_t res = 0;
  if (m == 1) return 0;
  if (m == 2) return (a & 1) && (b & 1);

  while (a > 0){
    if (a & 0x1)
      res = (res % m + b % m) % m;
    if (b > m)
      b = (b % m) << 1;
    else{
      if (b > (m >> 1))
        b = (b - m + b) % m;
      else 
        b <<= 1;
    }
    a >>= 1;
  }
  return (int64_t)res % m;*/
  if (m == 1) return 0;
  if (m == 2) return (a & 1) && (b & 1);

  int a_bin[bit];
  for (int i = 0; i < bit; i++) 
    a_bin[i] = 0;

  int len = 0;
  for (int i = 0; a && i < bit; i++){
    a_bin[i] = a % 2;
    a >>= 1;
    len += 1;
  }

  int64_t res = 0;
  //int64_t base = 0;
  for (int i = 0; i < len; i++){
    if (a_bin[i] == 1)
      res = (res % m +b % m) % m;
    if (b > m)
      b = (b % m) << 1;
    else{
      if (b > (m >> 1))
        b = b - m + b;
      else 
        b <<= 1;
    }
  }
  return res % m;
}
