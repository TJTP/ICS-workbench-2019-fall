#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*#define bit 20 //2的64次方为9223372036854775808，共19位
//#define COUNTING


typedef struct {
  int len;
  int s[bit * 2];
} NUM;


static void subtract(NUM *, NUM *);
static int64_t calculator(int64_t, int64_t, int64_t);
static bool compare(NUM *, NUM *);
static void mod(NUM *, NUM *);
static void mul(NUM *, NUM *, NUM *);




int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  clock_t start,finish;
  start=clock();
  int64_t ret = 0;
#ifdef COUNTING
  int64_t a1 = a, b1 = b, m1 = m, res;
  FILE *fp = fopen("../../rand_num","r");
  if(!fp){
    printf("can't open file\n");
    return false;
  }
  
  while(!feof(fp)){
    fscanf(fp,"%ld %ld %ld %ld", &a, &b, &m, &res);
    printf("a:%20ld b:%20ld m:%20ld ref_ans:%20ld my_ans:%20ld\n", a, b, m, res, calculator(a,b,m));
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
  for (int i = 0; i < bit * 2; i++) 
    product.s[i] = 0;

  mul(&product, &num1, &num2);
  mod(&product, &num3);
  
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
    num3->len+=1;
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


static void mod (NUM * num1, NUM * num2){
  while (compare(num1, num2))
    subtract(num1, num2);
}

static void subtract(NUM * num1,NUM * num2){// num1是大于等于num2的
  for (int i = 0; i < num2->len; i++){
    num1->s[i] -= num2->s[i];
    if (num1->s[i] < 0){
      for (int j = i+1; j < num1->len; j++){
        if(num1->s[j] > 0){//找到借位所在的位时
          num1->s[i] += 10;//当前位加上10
          num1->s[j] -= 1;//被借的位减去1
          break;
        }
        else 
          num1->s[j] = 9;
      }
    } 
  }

  if (num1->s[num1->len - 1] == 0)
    num1->len -= 1;
}*/


#include "multimod.h"
#include <string.h>
#include <stdio.h>

struct HP{
  int val[50]; // len(str(2**63-1)) = 19
  int len;
};

typedef struct HP HP;

void Init(HP* hp, int64_t num) {
  memset(hp->val, 0, sizeof(hp->val));
  int i;
  for(i = 0; num; i++) {
    hp->val[i] = num%10;
    num /= 10;
  }
  hp->len = (i>0) ? i : 1;
}

void Print(const HP hp) {
  int i;
  printf("len: %d, val: ", hp.len);
  for(i = hp.len-1; i >= 0; i--)
    printf("%d", hp.val[i]);
  printf("\n");
}

void Mul(HP* res, const HP a, const HP b) {
  res->len = a.len + b.len;
  memset(res->val, 0, sizeof(res->val));
  int i, j;
  for(i = 0; i < a.len; i++)
    for(j = 0; j < b.len; j++)
      res->val[i+j] += a.val[i] * b.val[j];
  for(i = 0; i < res->len; i++) {
    res->val[i+1] += res->val[i]/10;
    res->val[i] %= 10;
  }
  while(res->len > 1 && !res->val[res->len-1])
    res->len--;
}

int Compare(const HP a, const HP b) {
  if(a.len > b.len) {
    return 1;
  }else if(a.len < b.len) {
    return -1;
  }else{
    int i = a.len-1;
    while(i > 0 && a.val[i] == b.val[i])
      i--;
    return a.val[i]-b.val[i];
  }
}

void Sub(HP* res, const HP a, const HP b) { // Assume a>=b
  res->len = a.len;
  memset(res->val, 0, sizeof(res->val));

  int i, flag = 0;
  for(i = 0; i < a.len; i++) {
    res->val[i] = a.val[i] - flag;
    if(i < b.len)
      res->val[i] -= b.val[i];
    if(res->val[i] < 0) {
      res->val[i] += 10;
      flag = 1;
    } else {
      flag = 0;
    }
  }
  while(res->len > 1 && !res->val[res->len-1])
    res->len--;
}

void Mod(HP* res, const HP a, const HP b) {
  Init(res, 0);

  int i, j;
  for(i = a.len-1; i >= 0; i--) {
    if(!(res->len == 1 && res->val[0] == 0)) {
      for(j = res->len-1; j >= 0; j--)
        res->val[j+1] = res->val[j];
      res->len++;
    }
    res->val[0] = a.val[i];
    while(Compare(*res, b) >= 0) {
      Sub(res, *res, b);
    }
  }
}

void HPtoInt(int64_t* num, const HP hp) {
  int i;
  *num = 0;
  for(i = hp.len-1; i >= 0; i--)
    *num = (*num)*10 + hp.val[i];
}

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  HP hp_a, hp_b, hp_m, hp_c;
  Init(&hp_a, a);
  Init(&hp_b, b);
  Init(&hp_m, m);

  //Print(hp_a);
  //Print(hp_b);
  //Print(hp_m);

  Mul(&hp_c, hp_a, hp_b);
  Mod(&hp_c, hp_c, hp_m);
  HPtoInt(&m, hp_c);
  //printf("%ld\n", m);

  return m;
}

