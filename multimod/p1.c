#include "multimod.h"
#include <stdio.h>
#define bit 30
//2的64次方为18446744073709551616，共20位
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  
  char num1[bit];//,num2[bit],num3[bit];
  for(int i=0; a != 0||i<bit;i++){
    num1[i] = a%10+'0';
    printf("%c",num1[i]);
  }
  /*printf("\n");
  for(int i=0; b != 0||i<bit;i++){
    num2[i] = b%10+'0';
  }
  for(int i=0; m != 0||i<bit;i++){
    num3[i] = m%10+'0';
  }*/

  
  return -1;
}
