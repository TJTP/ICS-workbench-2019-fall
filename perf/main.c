#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

#define DECL(fn) void fn();

PROGRAMS(DECL)

static void run(void (*func)(), int rounds);
static uint64_t gettime();
static void (*lookup(const char *fn))();
//static char mul_n[15];//用于在run中创建文件时起名方便

int main(int argc, char **argv) {
  // TODO: parse arguments: set @func and @rounds
  if (argc > 4)
    assert("TOO MANY ARGS!!!\n");
  
  int rounds = 1;
  char func_name[15];

  for (int i = 1; i < argc; i++){// 第一个arg是执行文件名，所以直接跳过
    if (0 == strcmp(argv[i], "-r")){//
      i += 1;
      sscanf(argv[i], "%d", &rounds);
      if (rounds <= 0)
        assert("VALID INPUT: 'rounds' should be a positive #!!!\n");
    }
    else{
      strcpy(func_name, argv[i]);
      //strcpy(mul_n, argv[i]); 
    }  
  }
  //void (*func)() = lookup("dummy");
  //int rounds = 10;
  void (*func)() = lookup(func_name);
  
  run(func, rounds);
}

static uint64_t gettime() {
  // TODO: implement me!
  clock_t cur_clk;
  cur_clk = clock();
  //return time(NULL);
  return (double)cur_clk;
}

static void (*lookup(const char *fn))() {
  #define PAIR(fn) { #fn, fn },
  struct pair {
    const char *name;
    void *ptr;
  };
  struct pair lut[] = {
    PROGRAMS(PAIR)
  };

  for (int i = 0; i < LENGTH(lut); i++) {
    struct pair *p = &lut[i];
    if (strcmp(fn, p->name) == 0) return p->ptr;
  }
  return print_error;
}

static void run(void (*func)(), int rounds) {
  double *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  //system("python ./gen_rand_num_hi.py >rand_num");//生成限制a,b,m大小的随机数
  //system("python ./gen_rand_num_1.py >rand_num");//生成含1的位数限制的随机数
  for (int round = 0; round < rounds; round++) {
    double st = gettime();
    func();
    double ed = gettime();
    //elapsed[round] = ed - st;
    elapsed[round] = (ed - st) / CLOCKS_PER_SEC;
  }

  // TODO: display runtime statistics

  char fileName[] = "RUNTIME_of_p1"; //手动改吧
  //char fileName[] = "RUNTIME_of_p2"; //手动改吧
  //char fileName[] = "RUNTIME_of_p3"; //手动改吧

  FILE *fp = fopen(fileName,"a");
  if (fp == NULL)//文件不存在时，创建文件
    fp = fopen(fileName, "w");
  
  for (int i = 0; i < rounds; i++)
    fprintf(fp, "%f ", elapsed[i]);
  fprintf(fp, "\n");

  fclose(fp);
  


  free(elapsed);
}
