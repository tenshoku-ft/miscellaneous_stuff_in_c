#include "linear.h"

#include <stdlib.h>
#include <math.h>

void linear_del(linear_t*self){
	if(!self){
		return;
	}
	tensor_del(self->weight);
	tensor_del(self->bias);
	free(self);
}

int linear_new_uninitialized(linear_t**pself,size_t in_features,size_t out_features){
	linear_t*self;
	int ret;
	self=*pself=malloc(sizeof(**pself));
	if(!self){
		return !0;
	}
	size_t weight_size[2];
	weight_size[0]=in_features;
	weight_size[1]=out_features;
	if((ret=tensor_new_uninitialized(&(self->weight),weight_size,2))){
		free(self);
		*pself=NULL;
		return ret;
	}
	size_t bias_size[2];
	bias_size[0]=out_features;
	bias_size[1]=1;
	if((ret=tensor_new_uninitialized(&(self->bias),bias_size,2))){
		tensor_del(self->weight);
		free(self);
		*pself=NULL;
		return ret;
	}
	self->in_features=in_features;
	self->out_features=out_features;
	return 0;
}

int linear_forward(const linear_t*self,const tensor_t*input,tensor_t**output){
	int ret;
	if((ret=tensor_mul_matrix(output,input,self->weight))){
		return ret;
	}
	if((ret=tensor_add_asign(*output,self->bias))){
		return ret;
	}
	return 0;
}

int linear_init_xavier(linear_t*self,float(*normal)(void*,float,float),void*random_self){
	float stddev=1.0f/sqrtf((float)(self->in_features));
	size_t num_elements;
	num_elements=tensor_num_elements(self->weight);
	for(size_t i=0;i<num_elements;i++){
		self->weight->elements[i]=normal(random_self,0,stddev);
	}
	tensor_zero_out(self->bias);
	return 0;
}

int linear_init_kaiming(linear_t*self,float(*normal)(void*,float,float),void*random_self){
	float stddev=2.0f/sqrtf((float)(self->in_features));
	size_t num_elements;
	num_elements=tensor_num_elements(self->weight);
	for(size_t i=0;i<num_elements;i++){
		self->weight->elements[i]=normal(random_self,0,stddev);
	}
	tensor_zero_out(self->bias);
	return 0;
}

