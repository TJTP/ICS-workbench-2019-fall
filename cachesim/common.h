#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#define MEM_WIDTH 25
//#define MEM_SIZE (1 << 25) // 1MB  ?????
#define MEM_SIZE exp2(MEM_WIDTH) //32MB ?
#define BLOCK_WIDTH  6  // 64B
#define BLOCK_SIZE exp2(BLOCK_WIDTH)

typedef uint8_t bool;
#define true 1
#define false 0

void cycle_increase(int n);

//cache结构相关
typedef struct {
    uint32_t valid_bit; //有效位
    uint32_t dirty_bit; //脏(修改)位
    uint32_t tag;
    uint8_t data[BLOCK_SIZE]; //8 * 64
} cache_line;

uint32_t tot_width; //cache的总大小宽度
uint32_t row_num;  //cache的行数
uint32_t index_width; //cache的组号的幂(宽度)
uint32_t tag_width; //cache的标记的宽度
uint32_t asso_width; //每组的宽度

#define ADDR_INDEX(addr) ((addr >> BLOCK_WIDTH) & mask_with_len(index_width))
#define ADDR_TAG(addr) ((addr >> (MEM_WIDTH - tag_width)) & mask_with_len(tag_width))
#define ADDR_IN_BLOCK(addr) (addr & mask_with_len(BLOCK_WIDTH))
#define BLOCK_INDEX(addr) ((addr >> BLOCK_WIDTH) & mask_with_len(MEM_WIDTH - BLOCK_WIDTH)) 

#endif
