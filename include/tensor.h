#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct tensor_st tensor_t;

int tensor_zeroes(tensor_t**,size_t*,size_t);
int tensor_del(tensor_t*);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus


