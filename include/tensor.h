#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct{
	size_t dim;
	size_t*shape;
	float*elements;
}tensor_t;

void tensor_del(tensor_t*self);
int tensor_new_uninitialized(tensor_t**pself,const size_t*shape,size_t dim);
size_t tensor_num_elements(const tensor_t*self);
size_t tensor_new_from_float(tensor_t**pself,float val);
int tensor_dup(const tensor_t*self,tensor_t**ret);
int tensor_map_assign(tensor_t*self,float(*f)(float));
int tensor_zero_out(tensor_t*self);
int tensor_zeroes(tensor_t**pself,const size_t*shape,size_t dim);
int tensor_mul_matrix(tensor_t**ret,const tensor_t*a,const tensor_t*b);
int tensor_mul_assign_tensor_float(tensor_t*self,float b);
int tensor_have_same_shape(const tensor_t*a,const tensor_t*b);
int tensor_mul_hadamard(tensor_t**ret,const tensor_t*a,const tensor_t*b);
int tensor_add(tensor_t**ret,const tensor_t*a,const tensor_t*b);
int tensor_add_asign(tensor_t*self,const tensor_t*b);
int tensor_from_vector_to_column_vector(tensor_t*self);
int tensor_from_vector_to_row_vector(tensor_t*self);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

