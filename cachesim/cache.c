#include "common.h"
#include <inttypes.h>
#include <stdlib.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);
static uint32_t load_cache(uintptr_t);
static uint32_t substitude_cache(uintptr_t);

static uint64_t cycle_cnt = 0;
static uint32_t hit_cnt = 0;
static uint32_t miss_cnt = 0;
static cache_line *cache;//cache

void cycle_increase(int n) { cycle_cnt += n; }
void hit() { hit_cnt += 1; }
void miss() { miss_cnt += 1; }

// TODO: implement the following functions

// 从cache中读出`addr`地址处的4字节数据
// 若缺失, 需要先从内存中读入数据
uint32_t cache_read(uintptr_t addr) {
  uint32_t grp_idx = ADDR_INDEX(addr); //所给地址中的组号
  cache_line* base_addr = &cache[exp2(asso_width) * grp_idx]; //对应组的第一行

  //查看对应组中是否命中
  for (int i = 0; i < exp2(asso_width); i++){
    if ((base_addr[i].tag == ADDR_TAG(addr)) && base_addr[i].valid_bit == true){
      hit();
      uint32_t* ret = (uint32_t*)(base_addr[i].data + ADDR_IN_BLOCK(addr));
      return *ret;
    }
  }
  //如果没有命中，则需要加载cache
  miss();
  uint32_t idx_in_grp = load_cache(addr);
  uint32_t* ret = (uint32_t*)(base_addr[idx_in_grp].data + ADDR_IN_BLOCK(addr));
  return *ret;

}

// 往cache中`addr`地址所属的块写入数据`data`, 写掩码为`wmask`
// 例如当`wmask`为`0xff`时, 只写入低8比特
// 若缺失, 需要从先内存中读入数据
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  uint32_t grp_idx = ADDR_INDEX(addr); //所给地址中的组号
  cache_line* base_addr = &cache[exp2(asso_width) * grp_idx]; //对应组的第一行

  //查看对应组中是否命中
  for (int i = 0; i < exp2(asso_width); i++){
    if ((base_addr[i].tag == ADDR_TAG(addr)) && base_addr[i].valid_bit == true){
      uint32_t *addr_modified = (uint32_t*)(base_addr[i].data + ADDR_IN_BLOCK(addr));
      *addr_modified = (*addr_modified & ~wmask) | (data & wmask);
      base_addr[i].dirty_bit = true;
      return;
    }
  }

  //如果没有命中，则需要加载cache
  uint32_t idx_in_grp =  load_cache(addr);
  uint32_t *addr_modified = (uint32_t*)(base_addr[idx_in_grp].data + ADDR_IN_BLOCK(addr));
  *addr_modified = (*addr_modified & ~wmask) | (data & wmask);
  base_addr[idx_in_grp].dirty_bit = true;
}

// 初始化一个数据大小为`2^total_size_width`B, 关联度为`2^associativity_width`的cache
// 例如`init_cache(14, 2)`将初始化一个16KB, 4路组相联的cache
// 将所有valid bit置为无效即可
void init_cache(int total_size_width, int associativity_width) {
  assert(total_size_width >= associativity_width);

  row_num = exp2(total_size_width - BLOCK_WIDTH);
  cache = (cache_line*)malloc(sizeof(cache_line) * row_num);

  index_width = (total_size_width - BLOCK_WIDTH) - associativity_width;
  tag_width = MEM_WIDTH - BLOCK_WIDTH - index_width;
  asso_width = associativity_width;

  for (int i = 0; i < row_num; i++){
    cache[i].valid_bit = false;
    cache[i].dirty_bit = false;
  }
}

void display_statistic(void) {
  double hit_ratio = (double)hit_cnt / (hit_cnt + miss_cnt);
  printf("HIT: %d, MISS: %d, HIT_RATIO: %f\n", hit_cnt, miss_cnt, hit_ratio);
}

uint32_t load_cache(uintptr_t addr){//返回所在组中的行号
  uint32_t grp_idx = ADDR_INDEX(addr); //所给地址中的组号
  cache_line* base_addr = &cache[exp2(asso_width) * grp_idx]; //对应组的第一行

  //从内存中取相应块的内容存入对应组的某一行
  for (uint32_t i = 0; i <exp2(asso_width); i++ ){
    if (base_addr[i].valid_bit == false){//如果有未被使用的行
      mem_read(BLOCK_INDEX(addr), base_addr[i].data);
      base_addr[i].valid_bit = true;
      base_addr[i].tag = ADDR_TAG(addr);
      return i;
    }
  }

  return substitude_cache(addr);
}

uint32_t substitude_cache(uintptr_t addr){
  uint32_t grp_idx = ADDR_INDEX(addr); //所给地址中的组号
  cache_line* base_addr = &cache[exp2(asso_width) * grp_idx]; //对应组的第一行
  uint32_t idx_in_grp = rand() % exp2(asso_width);
  
  if (base_addr[idx_in_grp].dirty_bit == true)//如果是修改过的cache，需要先写回内存
    mem_write(BLOCK_INDEX(addr), base_addr[idx_in_grp].data);
  
  mem_read(BLOCK_INDEX(addr), base_addr[idx_in_grp].data);
  base_addr[idx_in_grp].valid_bit = true;
  base_addr[idx_in_grp].tag = ADDR_TAG(addr);

  return idx_in_grp;
}