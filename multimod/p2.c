#include "multimod.h"
#include <time.h>
#include <stdio.h>

#define bit 63

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int bnum1[bit];
  for (int i = 0;i < bit;i++){
    if((a>>i)&0b1) bnum1[i]=1;
  }
  for(int i = 62;i>=0;i--) printf("%d",bnum1[i]);
  printf("\n");
  return -2;
}