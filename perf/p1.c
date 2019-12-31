//#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define bit 20 //2的64次方为9223372036854775808，共19位
#define COUNTING


typedef struct {
  int len;
  int s[bit * 2];
} NUM;

static int64_t calculator(int64_t, int64_t, int64_t);
static void subtract(NUM *, NUM *);
static bool compare(NUM *, NUM *);
static void mod(NUM *, NUM, NUM );
static void mul(NUM *, NUM *, NUM *);

//int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  //clock_t start,finish;
  //start=clock();
  //int64_t ret = 0;
int64_t multimod_p1(){
 

#ifdef COUNTING
  int64_t a1 = a, b1 = b, m1 = m, res;
  FILE *fp = fopen("../../rand_num","r");
  if(!fp){
    printf("can't open file\n");
    return false;
  }
  int cnt_right = 0;
  int cnt_total = 0;
  while(!feof(fp)){
    fscanf(fp,"%ld %ld %ld %ld",&a, &b, &m, &res);
    uint64_t ans = calculator(a,b,m);
    bool cor = res - ans == 0 ? true : false;
    if (cor)
      cnt_right += 1;
    printf("a:%20ld b:%20ld m:%20ld ref_ans:%20ld my_ans:%20ld cor:%s\n", a, b, m, res, ans, cor ? "RIGHT" : "WRONG");
    cnt_total += 1;
  }
  fclose(fp);
  printf("There are %d samples in total, and # of correct samples is %d\n", cnt_total, cnt_right);
  //ret = calculator(a1,b1,m1);
#endif
#ifndef COUNTING
  //ret = calculator(a,b,m);
  printf("DO NOTHING\n");
  return 0;
#endif

  //finish=clock();
  //double duration = (double)(finish-start)/CLOCKS_PER_SEC;
  //printf("%f seconds on p1.c and the answer of input is ",duration);
  //return ret;
  return 0;
}

static int64_t calculator(int64_t a,int64_t b, int64_t m){
  NUM num1, num2, num3;
  num1.len = 0, num2.len = 0, num3.len = 0;

  while(a){
    num1.s[num1.len] = a % 10;
    a /= 10;
    num1.len++;
  }
  while(b){
    num2.s[num2.len] = b % 10;
    b /= 10;
    num2.len++;
  }
  while(m){
    num3.s[num3.len] = m%10;
    m /= 10;
    num3.len++;
  }

  NUM product;
  product.len = num1.len + num2.len - 1;
  memset(product.s, 0, sizeof(product.s));

  mul(&product, &num1, &num2);
  mod(&product, product, num3);
  
  int64_t result = 0;
  int64_t base = 1;
  for(int i = 0; i < product.len; i++){
    result += product.s[i] * base;
    base *= 10;
  }
  return result;
}

static void mul(NUM * num3, NUM * num1,NUM * num2){
  for(int i = 0; i < num1->len; i++){
    for(int j = 0; j<num2->len; j++)
      num3->s[i+j] += num1->s[i] * num2->s[j];
  }

  bool update_len = false;
  for(int i = 0; i < num3->len; i++){
    if(num3->s[i] >= 10){
      num3->s[i+1] += num3->s[i]/10;
      num3->s[i] %= 10;
      if (i == num3->len - 1)
        update_len = true;
    }
  }
  if (update_len) 
    num3->len += 1;
}

bool compare(NUM * num1, NUM * num2){//num1比num2大或相等时，返回true
  if (num1->len < num2->len) 
    return false;
  else if(num1->len > num2->len)
    return true;

  for (int i = num1->len - 1; i >= 0; i--){
    if (num1->s[i] > num2->s[i]) 
      return true;
    else if (num1->s[i] < num2->s[i]) 
      return false;
  }
  return true;
}


static void mod (NUM * res, NUM  num1, NUM  num2){
  memset(res, 0, sizeof(res->s));
  res->len = 0;

  int i, j;
  for(i = num1.len-1; i >= 0; i--) {
    if(!(res->len == 1 && res->s[0] == 0)) {
      for(j = res->len-1; j >= 0; j--)
        res->s[j+1] = res->s[j];
      res->len++;
    }
    res->s[0] = num1.s[i];
    while(compare(res, &num2)) {
      subtract(res, &num2);
    }
  }
}


static void subtract(NUM * num1, NUM * num2){// num1是大于等于num2的
  int carry = 0;
  for (int i = 0; i < num1->len; i++){
    num1->s[i] -= carry;
    if (i < num2->len)
      num1->s[i] -= num2->s[i];
    if (num1->s[i] < 0){
      num1->s[i] += 10;
      carry = 1;
    }
    else 
      carry = 0;
  }
  while (num1->len > 1 && num1->s[num1->len -1] == 0)
    num1->len -= 1;
}


