#include "multimod.h"
#include <stdio.h>
#include <string.h>
#define bit 20
//2的64次方为18446744073709551616，共20位
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int num1[bit],num2[bit],num3[bit];
  int l1=0,l2=0,l3=0;
  while(a){
    num1[l1]=a%10;
    a/=10;
    l1++;
  }
  while(b){
    num2[l2]=b%10;
    b/=10;
    l2++;
  }
  while(m){
    num3[l3]=m%10;
    m/=10;
    l3++;
  }
  printf("use it once %d\n",num3[0]);
  int t[bit*2];
  for (int i=0;i<bit*2;i++) t[i]=0;
  for(int i=0;i<l1;i++)
    for(int j =0; j<l2;j++)
      t[i+j]+=num1[i]*num2[j];
  
  for(int i = 0;i<l1+l2;i++){
    if(t[i] >=10){
      t[i+1]+=t[i]/10;
      t[i]%10;
    }
  }
  int64_t result=0;
  int64_t base = 1;
  for(int i = 0;i<l1+l2;i++){
    result+=t[i]*base;
    base*=10;
  }
  
  
  
  return result;
}
