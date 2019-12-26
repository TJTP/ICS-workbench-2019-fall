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
  asm("mov %1, -0x18(%%rbp)\n"
      "movl $0x0, -0x8(%%rbp)\n" // i
      "jmp dest1\n"
      "dest3: mov -0x8(%%rbp), %%eax\n"
      "mov -0x18(%%rbp), %%rdx\n"
      "mov %%eax, %%ecx\n"
      "shr %%cl, %%rdx\n"
      "mov %%rdx, %%rax\n"
      "and $0x1, %%eax\n"//???
      "test %%rax,%%rax\n"
      "je dest2\n"
      "addl $0x1, %0\n"
      "dest2: addl $0x1, -0x8(%%rbp)\n"// i++
      "dest1: cmpl $0x3f, -0x8(%%rbp)\n"
      "jle dest3\n"
      : "+r"(cnt) //占位符 %0
      : "r"(n) //占位符 %1
      :"%rax", "%eax", "%ecx","%rdx","%cl"
      
  );
  return cnt;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  void * ret = dest;
  asm("mov %0, -0x18(%%rbp)\n"//dest
      "mov %1, -0x20(%%rbp)\n"//src
      "mov %2, -0x28(%%rbp)\n"//n
      "mov -0x18(%%rbp), %%rax\n"
      //"mov %%rax, -0x8(rbp)\n" //void * ret = dst
      "mov %%rax, %3\n"//void * ret = dst
      "jmp dest4\n"
      "dest5: mov -0x20(%%rbp), %%rax\n"
      "movzbl (%%rax), %%edx\n"
      "mov -0x18(%%rbp), %%rax\n"
      "mov %%dl, (%%rax)\n"
      "addq $0x1, -0x18(%%rbp)\n"
      "addq $0x1, -0x20(%%rbp)\n"
      "dest4: mov -0x28(%%rbp), %%rax\n"
      "lea -0x1(%%rax), %%rdx\n"//n--
      "mov %%rdx, -0x28(%%rbp)\n"
      "test %%rax, %%rax\n"//n > 0
      "jne dest5\n"
      //"mov -0x8(%%rbp), %%rax\n" //将ret放进rax，以便返回
      //"pop %%rbp\n"
      //"retq\n"
      :
      :"r"(dest), "r"(src), "r"(n), "r"(ret) //占位符0, 1, 2, 3
      :"%rax", "%edx", "%rdx", "%dl"
  );
  return ret;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  asm(/*"mov %0, %%edi\n"
      "xor %%esi, %%esi\n"
      "mov %%rbx, (%%rdi)\n"
      "mov %%rbp, %%rax\n"
      "mov %%rax, 0x8(%%rdi)\n"
      "mov %%r12, 0x10(%%rdi)\n"
      "mov %%r13, 0x18(%%rdi)\n"
      "mov %%r14, 0x20(%%rdi)\n"
      "mov %%r15, 0x28(%%rdi)\n"
      "lea 0x8(%%rsp), %%rdx\n"//rsp的旧值
      "mov %%rdx, 0x30(%%rdi)\n"
      "mov (%%rsp), %%rax\n"//pc的值
      "mov %%rax, 0x38(%%rdi)\n" 
      :
      :"m"(env) //占位符0
      :"%rax", "%rdx", "%rdi", "%edi", "memory"*/
      "mov %[env], %%rdx\n"
      "mov %%rbx, (%%rdx)\n" // * 保存rbx
      "mov (%%rsp), %%rax\n"
      "mov %%rax, 0x8(%%rdx)\n" // * rsp存放rbp的旧址
      "mov %%r12, 0x10(%%rdx)\n"
      "mov %%r13, 0x18(%%rdx)\n"
      "mov %%r14, 0x20(%%rdx)\n"
      "mov %%r15, 0x28(%%rdx)\n"
      "lea 0x10(%%rsp), %%rax\n"
      "mov %%rax, 0x30(%%rdx)\n" // * rsp+10的地址是rsp的旧值
      "mov 0x8(%%rsp), %%rax\n"
      "mov %%rax, 0x38(%%rdx)\n"  // * rsp+8存放pc
      : 
      : [env] "m"(env)
      : "%rax", "cc", "memory"
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
