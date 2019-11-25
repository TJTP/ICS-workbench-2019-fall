#include "multimod.h"
#include <time.h>
#include <stdio.h>

#define bit 20
//2的64次方为18446744073709551616，共20位

typedef struct {
  int len;
  int s[bit*2];
} NUM;
extern static NUM subtract(NUM t,NUM m);

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  return -2;
}