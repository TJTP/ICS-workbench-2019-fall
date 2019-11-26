#include "multimod.h"
#include <time.h>
#include <stdio.h>

#define bit 63

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int bnum1[bit];
  for (int i = 0;i < bit;i++){
    if((a>>i)&0b1) bnum1[i]=1;
    else bnum1[i]=0;
  }
  int64_t r = 0;
  int64_t base = 0;
  for (int i = 0; i<bit; i++){
    r+=(bnum1[i]*(b<<base))%m;
    base+=1;
  }
  
  //for(int i = 62;i>=0;i--) printf("%d",bnum1[i]);
  //printf("\n");
  return r;
}