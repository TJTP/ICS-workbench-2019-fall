#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define bit 63
#define COUNTING

static int64_t calculator(int64_t a, int64_t b, int64_t m);

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  clock_t start,finish;
  start=clock();
  int64_t a1=a,b1=b,m1=m;
  int64_t ret = 0;
#ifdef COUNTING
   srand((unsigned)time(NULL));
  for(int i = 1;i<=20;i++){
    
    //0x8000000000000000
    a = rand() % 100000;
    b = rand() % 100000;
    m = rand() % 100000;
    printf("a is %ld, b is %ld, m is %ld, test sample %d is %ld\n",a,b,m,i,calculator(a,b,m));
  }
  ret = calculator(a1,b1,m1);
#endif
#ifndef COUNTING
  ret = calculator(a,b,m);
#endif
  finish=clock();
  double duration = (double)(finish-start)/CLOCKS_PER_SEC;
  printf("%f seconds on p2.c and the answer is \n",duration);
  return ret;
  
}


static int64_t calculator(int64_t a, int64_t b, int64_t m){
  int bnum1[bit];
  for (int i = 0;i < bit;i++){
    if((a>>i)&0b1) bnum1[i]=1;
    else bnum1[i]=0;
  }
  int64_t r=0;
  if(b>(m>>1)&&b<m){
    for(int i = 0;i<bit;i++){
      int tmp = b;
      for(int j = 0;j<i;j++){
        tmp=(tmp-m+tmp)%m;
      }
      r=r+bnum1[i]*tmp;
    }
  }
  else{
    for(int i = 0;i<bit;i++){
      int tmp = b;
      r+=(bnum1[i]*(tmp<<i))%m;
    }
    r%=m;
  }

 
  return r;
}
