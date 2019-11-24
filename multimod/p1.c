#include "multimod.h"
#include <stdio.h>
#include <string.h>
#define bit 30
//2的64次方为18446744073709551616，共20位
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  
  char temp1[bit],temp2[bit],temp3[bit];
  for(int i=0; a != 0&&i<bit;i++){
    temp1[i] = a%10+'0';
    a/=10;
  }
  for(int i=0; b != 0&&i<bit;i++){
    temp2[i] = b%10+'0';
    b/=10;
  }
  for(int i=0; m != 0&&i<bit;i++){
    temp3[i] = m%10+'0';
    m/=10;
  }
  /*int l1 = strlen(temp1),l2 = strlen(temp2),l3 = strlen(temp3);
  int num1[l1],num2[l2],num3[l3];
  for(int i = 0,j=l1-1;i<l1;i++,j--) num1[i] = temp1[j]-'0';
  for(int i = 0,j=l2-1;i<l2;i++,j--) num2[i] = temp2[j]-'0';
  for(int i = 0,j=l3-1;i<l3;i++,j--) num3[i] = temp3[j]-'0';*/

  printf("%s\n",temp1);
  printf("%s\n",temp2);
  for (int i = 0;i<strlen(temp3);i++)
    printf("%c",temp3[i]);
  printf("\n");
  printf("%ld",strlen(temp3));
  
  
  return -1;
}
