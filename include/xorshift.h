#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct random_xorshift128_st random_xorshift128_t;

void random_xorshift128_init(random_xorshift128_t**,uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t random_xorshift128_next_u32(random_xorshift128_t*);
float random_xorshift128_uniform_f32(random_xorshift128_t*);
float random_xorshift128_uniform_between_f32(random_xorshift128_t*,float,float);
float random_xorshift128_standard_normal_f32(random_xorshift128_t*);
float random_xorshift128_normal_f32(random_xorshift128_t*,float,float);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

