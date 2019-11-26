#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define bit 20
//2的64次方为9223372036854775808，共19位
//#define COUNTING

typedef struct {
  int len;
  int s[bit*2];
} NUM;

static NUM subtract(NUM t,NUM m);
static int64_t calculator(int64_t a,int64_t b, int64_t m);
static bool compare(NUM t, NUM m);
static NUM mod(NUM t, NUM m);
static NUM mul(NUM a, NUM b);

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  clock_t start,finish;
  start=clock();
  int64_t ret = 0;
#ifdef COUNTING
  int64_t a1=a,b1=b,m1=m;
  FILE *fp = fopen("../../rand_num","r");
  if(!fp){
    printf("can't open file\n");
    return false;
  }
  
  while(!feof(fp)){
    fscanf(fp,"%ld %ld %ld",&a,&b,&m);
    int64_t cal = calculator(a,b,m);
    printf("a:%20ld b:%20ld m:%20ld ans:%20ld\n",a,b,m,cal);
  }
  fclose(fp);
  ret = calculator(a1,b1,m1);
#endif
#ifndef COUNTING
  ret = calculator(a,b,m);
#endif
  finish=clock();
  double duration = (double)(finish-start)/CLOCKS_PER_SEC;
  printf("%f seconds on p1.c and the answer of input is ",duration);
  return ret;
}

static int64_t calculator(int64_t a,int64_t b, int64_t m){
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

  NUM tmp = mul(num1,num2);
  printf("%d\n",tmp.len);

  NUM r = mod(tmp,num3);
  int64_t result = 0;
  int64_t base = 1;
  for(int i = 0;i<r.len;i++){
    result+=r.s[i]*base;
    base*=10;
  }
  return result;
}

static NUM mul(NUM a,NUM b){
  NUM res;
  res.len=a.len+b.len-1;
  for (int i=0;i<bit*2;i++)  res.s[i]=0;

  for(int i=0;i<a.len;i++){
    for(int j =0; j<b.len;j++)
      res.s[i+j] += a.s[i]*b.s[j];
  }

  for(int i = 0;i<res.len;i++){
    if(res.s[i] >=10){
      res.s[i+1] += res.s[i]/10;
      res.s[i] %= 10;
    }
  }
  if (res.s[res.len] > 0) res.len+=1;
  return res;
}
bool compare(NUM t, NUM m){
  if(t.len<m.len) return false;
  else if(t.len >m.len) return true;
  for (int i = t.len-1;i>=0;i--){
    if(t.s[i] > m.s[i]) return true;
    else if(t.s[i] < m.s[i]) return false;
  }
  return true;
}

static NUM mod (NUM t, NUM m){
  NUM tmp = t;
  int64_t q = 0;
  while(compare(tmp,m)){
    tmp = subtract(tmp,m);
    q++;
  }
  return tmp;
}
static NUM subtract(NUM t,NUM m){   
  for (int i=0;i<m.len;i++){//逐位作差
    t.s[i] -= m.s[i];
    if(t.s[i] < 0){
      for (int j = i+1; j<t.len;j++){
        if(t.s[j]>0){//找到借位所在的位时
          t.s[i] += 10;//当前位加上10
          t.s[j] -= 1;//被借的位减去1
          for(int k=j-1;k>i;k--){
            t.s[k]=9;
            k--;
          }
          break;
        }
      }
    }
  }
  if (t.s[t.len-1]==0) t.len-=1;
  return t;
  
  
}


