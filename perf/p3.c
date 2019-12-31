//#include "multimod.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define COUNTING

static int64_t calculator(int64_t a, int64_t b, int64_t m);

int64_t multimod_p3(int64_t a, int64_t b, int64_t m) {
  //clock_t start,finish;
  //start=clock();
  
  int64_t ret = 0; 

#ifdef COUNTING
  int64_t a1=a, b1=b, m1=m, res;
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
  ret = calculator(a1,b1,m1);
#endif
#ifndef COUNTING
  ret = calculator(a,b,m);
#endif

  //finish=clock();
  //double duration = (double)(finish-start)/CLOCKS_PER_SEC;
  //printf("%f seconds on p3.c and the answer is ",duration);
  printf("The answer is: %d\n", ret);
  return ret;
}

static int64_t calculator(int64_t a, int64_t b, int64_t m){
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}
