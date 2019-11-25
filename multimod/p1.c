#include "multimod.h"
#include <stdio.h>
#define bit 20
//2的64次方为18446744073709551616，共20位

typedef struct {
  int len;
  int s[bit*2];
} NUM;
extern NUM subtract(NUM t,NUM m);

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

  //return num3.len;
  NUM tmp; 
  tmp.len=num1.len+num2.len-1;
  for (int i=0;i<bit*2;i++)  tmp.s[i]=0;

  for(int i=0;i<num1.len;i++){
    for(int j =0; j<num2.len;j++)
      tmp.s[i+j]+=num1.s[i]*num2.s[j];
  }

  for(int i = 0;i<num1.len+num2.len;i++){
    if(tmp.s[i] >=10){
      tmp.s[i+1] += tmp.s[i]/10;
      tmp.s[i] %= 10;
    }
    if (i == num1.len+num2.len-1 && tmp.s[i] != 0) tmp.len+=1;
  }
  //return tmp.len;

  if(tmp.len < num3.len){//被除数长度小于除数长度时
    int64_t result = 0;
    int64_t base = 1;
    for(int i = 0;i<tmp.len;i++){
      result += tmp.s[i]*base;
      base *= 10;
    }
    return result;
  }

  NUM r = subtract(tmp,num3);
  int64_t result = 0;
  int64_t base = 1;
  for(int i = 0;i<r.len;i++){
    result+=r.s[i]*base;
    base*=10;
  }
  return r.s[2];
}


NUM subtract(NUM t,NUM m){
  NUM r=t;
  while(1){
    r=t;

    for (int i=0;i<m.len;i++){//逐位作差

      t.s[i] -= m.s[i];

      if(t.s[i]<0){
        int j = i+1;
        for (;j<t.len;){
          if(t.s[j]>0){//借到位之后
            t.s[i] += 10;
            t.s[j] -= 1;
            int k = j-1;
            while(k>i){
              t.s[k]=9;
              k--;
            }
            break;
          }
          j++;
        }
        if(j == t.len) return r;//此时被减数已经小于减数，即得到余数
        if(j == t.len-1 && t.s[j]==0) t.len-=1;//最高位变为0后，长度缩小为1；
      }

      if(t.s[t.len-1]==0)  t.len-=1;
    }
  }
  return r;
  
  
}


