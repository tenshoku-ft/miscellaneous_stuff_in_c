#include "tensor.h"

#include <stdlib.h>
#include <string.h>

struct tensor_st{
	size_t*shape;
	size_t dim;
	float*elements;
};

static int tensor_new_uninitialized(tensor_t**pself,size_t*shape,size_t dim){
	if(!pself){
		return !0;
	}
	if(dim==0){
		return !0;
	}
	if(!(*pself=malloc(sizeof(**pself)))){
		return !0;
	}
	if(!((*pself)->shape=malloc(sizeof((*pself)->shape[0])*dim))){
		free(*pself);
		*pself=NULL;
		return !0;
	}
	memcpy((*pself)->shape,shape,sizeof((*pself)->shape[0])*dim);
	size_t num_elements=1;
	for(int i=0;i<dim;i++){
		num_elements*=shape[i];
	}
	if(!((*pself)->elements=malloc(sizeof((*pself)->elements[0])*num_elements))){
		free((*pself)->shape);
		free(*pself);
		*pself=NULL;
	}
	return 0;
}

int tensor_zeroes(tensor_t**pself,size_t*shape,size_t dim){
	int ret=tensor_new_uninitialized(pself,shape,dim);
	if(ret){
		return ret;
	}
	size_t num_elements=1;
	for(int i=0;i<dim;i++){
		num_elements*=shape[i];
	}
	for(int i=0;i<num_elements;i++){
		(*pself)->elements[i]=0.0;
	}
	return 0;
}

int tensor_del(tensor_t*self){
	free(self->shape);
	free(self->elements);
	free(self);
	return 0;
}

