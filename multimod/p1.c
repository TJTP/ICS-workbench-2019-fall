#include "multimod.h"
#include <stdio.h>
#include<string.h>
#define bit 30
//2的64次方为18446744073709551616，共20位
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  
  int num1[bit];//num2[bit],num3[bit];
  for(int i=0; a != 0&&i<bit;i++){
    num1[i] = a%10;
    a/=10;
  }
  /*for(int i=0; b != 0||i<bit;i++){
    num2[i] = b%10;
    b/=10;
  }
  for(int i=0; m != 0||i<bit;i++){
    num3[i] = m%10;
    m/=10;
  }*/
  for(int i = strlen(num1)-1;i>=0;i--)
    printf("%d",num1[i]);
  printf("\n");
  
  return -1;
}
