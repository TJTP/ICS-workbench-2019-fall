#include "multimod.h"
#include <stdio.h>
#include <string.h>
#define bit 20
//2的64次方为18446744073709551616，共20位

typedef struct {
  int len;
  int s[bit*2];
} NUM;
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  NUM num1,num2,num3;
  num1.len=0,num2.len=0,num3.len=0;
  while(a){
    num1.s[num1.len]=a%10;
    a/=10;
    num1.len++;
  }
  while(b){
    num2.s[num2.len]=b%10;
    b/=10;
    num2.len++;
  }
  while(m){
    num3.s[num3.len]=m%10;
    m/=10;
    num3.len++;
  }

  printf("use it once %d\n",num3.s[0]);

  NUM tmp; 
  tmp.len=num1.len+num2.len-1;
  for (int i=0;i<bit*2;i++) tmp.s[i]=0;
  for(int i=0;i<num1.len;i++){
    for(int j =0; j<num2.len;j++)
      tmp.s[i+j]+=num1.s[i]*num2.s[j];
  }

  for(int i = 0;i<num1.len+num2.len;i++){
    if(tmp.s[i] >=10){
      tmp.s[i+1]+=tmp.s[i]/10;
      tmp.s[i]%=10;
      if (i == num1.len+num2.len-1) tmp.len+=1;
    }
  }
  
  if(tmp.len < num3.len
      ||(tmp.len==num3.len && tmp.s[tmp.len-1]<num3.s[num3.len-1])){//被除数小于除数时
    int64_t result = 0;
    int64_t base = 1;
    for(int i = 0;i<tmp.len;i++){
      result += tmp.s[i]*base;
      base *= 10;
    }
    return result;
  }






  
  
  
  return -1;
}


