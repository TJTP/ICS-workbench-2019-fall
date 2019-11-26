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