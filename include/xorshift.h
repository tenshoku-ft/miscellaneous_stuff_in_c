#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct random_xorshift128_st random_xorshift128_t;

void random_xorshift128_init(random_xorshift128_t*,uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t random_xorshift128_next_u32(random_xorshift128_t*);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

