#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  // TODO: implement
  asm("add %1, %0;"
      : "+r"(a)
      : "r"(b)
  );
  return a;
}

int asm_popcnt(uint64_t n) {
  // TODO: implement
  int cnt = 0;
  asm("mov %%rdi, -0x18(%%rbp)\n"
      "movl $0x0, -0x8(%%rbp)\n" // i
      "jmp dest1\n"
      "dest3: mov -0x8(%%rbp), %%eax\n"
      "mov -0x18(%%rbp), %%rdx\n"
      "mov %%eax, %%ecx\n"
      "shr 0x1, %%rdx\n"
      "mov %%rdx, %%rax\n"
      "and $0x1, %%eax\n"//???
      "test %%rax,%%rax\n"
      "je dest2\n"
      "addl $0x1, %0\n"
      "dest2: addl $0x1, -0x8(%%rbp)\n"// i++
      "dest1: cmpl $0x3f, -0x8(%%rbp)\n"
      "jle dest3\n"
      : "+g"(cnt)
      : "r"(n)
      :"%rax", "%eax", "%ecx","%rdx"
  );
  return cnt;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  return NULL;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
