#pragma once

#include "tensor.h"
#include "layer.h"

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct{
	size_t in_features;
	size_t out_features;
	tensor_t*weight;
	tensor_t*bias;
}linear_t;

void linear_del(linear_t*self);
int linear_new_uninitialized(linear_t**pself,size_t in_features,size_t out_features);
int linear_init_xavier(linear_t*self,float(*normal)(void*,float,float),void*random_self);
int linear_init_kaiming(linear_t*self,float(*normal)(void*,float,float),void*random_self);
#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

