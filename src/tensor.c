#include "tensor.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void tensor_del(tensor_t*self){
	if(!self){
		return;
	}
	free(self->elements);
	free(self->shape);
	free(self);
}

int tensor_new_uninitialized(tensor_t**pself,const size_t*shape,size_t dim){
	if(!pself){
		return !0;
	}
	if((dim==0)||(!shape)){
		*pself=NULL;
		return !0;
	}
	size_t num_elements=1;
	for(size_t i=0;i<dim;i++){
		num_elements*=shape[i];
	}
	if(num_elements==0){
		*pself=NULL;
		return !0;
	}
	tensor_t*self;
	self=*pself=malloc(sizeof(**pself));
	if(!self){
		*pself=NULL;
		return !0;
	}
	self->dim=dim;
	size_t size_of_shape=sizeof(*(self->shape))*dim;
	self->shape=malloc(size_of_shape);
	if(!(self->shape)){
		free(self);
		*pself=NULL;
		return !0;
	}
	memcpy(self->shape,shape,size_of_shape);
	self->elements=malloc(num_elements*sizeof(*(self->elements)));
	if(!(self->elements)){
		free(self->shape);
		free(self);
		*pself=NULL;
		return !0;
	}
	return 0;
}

size_t tensor_new_from_float(tensor_t**pself,float val){
	int ret;
	size_t one=1;
	ret=tensor_new_uninitialized(pself,&one,one);
	if(ret){
		return ret;
	}
	(*pself)->elements[0]=val;
	return 0;
}

size_t tensor_num_elements(const tensor_t*self){
	size_t num_elements=1;
	for(size_t i=0;i<self->dim;i++){
		num_elements*=self->shape[i];
	}
	return num_elements;
}

int tensor_dup(const tensor_t*self,tensor_t**ret){
	int res=tensor_new_uninitialized(ret,self->shape,self->dim);
	if(res){
		return res;
	}
	size_t num_elements=tensor_num_elements(self);
	for(size_t i=0;i<num_elements;i++){
		(*ret)->elements[i]=self->elements[i];
	}
	return 0;
}

int tensor_map_assign(tensor_t*self,float(*f)(float)){
	size_t num_elements=tensor_num_elements(self);
	for(size_t i=0;i<num_elements;i++){
		self->elements[i]=f(self->elements[i]);
	}
	return 0;
}

int tensor_zero_out(tensor_t*self){
	size_t num_elements=tensor_num_elements(self);
	for(size_t i=0;i<num_elements;i++){
		self->elements[i]=0.0f;
	}
	return 0;
}

int tensor_zeroes(tensor_t**pself,const size_t*shape,size_t dim){
	int ret;
	ret=tensor_new_uninitialized(pself,shape,dim);
	if(ret){
		return ret;
	}
	ret=tensor_zero_out(*pself);
	if(ret){
		return ret;
	}
	return 0;
}

int tensor_mul_assign_tensor_float(tensor_t*self,float b){
	size_t num_elements=tensor_num_elements(self);
	for(size_t i=0;i<num_elements;i++){
		self->elements[i]*=b;
	}
	return 0;
}

int tensor_mul_matrix(tensor_t**ret,const tensor_t*a,const tensor_t*b){
	int res;
	// a is scalar
	if((a->dim==1)&&(a->shape[0]=1)){
		res=tensor_dup(b,ret);
		if(res){
			return res;
		}
		res=tensor_mul_assign_tensor_float(*ret,a->elements[0]);
		if(res){
			return res;
		}
		return 0;
	}
	// b is scalar
	if((b->dim==1)&&(b->shape[0]=1)){
		res=tensor_dup(a,ret);
		if(res){
			return res;
		}
		res=tensor_mul_assign_tensor_float(*ret,b->elements[0]);
		if(res){
			return res;
		}
		return 0;
	}
	// both a and b are vector with same shape
	if((a->dim==1)&&(b->dim==1)&&(a->shape[0]==b->shape[0])){
		float product=0;
		for(size_t i=0;i<a->shape[0];i++){
			product+=a->elements[i]*b->elements[i];
		}
		res=tensor_new_from_float(ret,product);
		if(res){
			return res;
		}
		return 0;
	}
	// matrix multiplication
	if((a->dim==2)&&(b->dim==2)&&(a->shape[1]==b->shape[0])){
		size_t ret_shape[2];
		ret_shape[0]=a->shape[0];
		ret_shape[1]=b->shape[1];
		res=tensor_zeroes(ret,ret_shape,2);
		if(res){
			return res;
		}
		for(size_t i=0;i<a->shape[0];i++){
			for(size_t k=0;k<a->shape[1];k++){
				for(size_t j=0;j<b->shape[1];j++){
					(*ret)->elements[(*ret)->shape[0]*i+j]+=(a->elements[a->shape[0]*k+i])*(b->elements[b->shape[0]*j+k]);
				}
			}
		}
		return 0;
	}
	// otherwise currently unimplemented
	return !0;
}

int tensor_have_same_shape(const tensor_t*a,const tensor_t*b){
	if(a->dim!=b->dim){
		return 0;
	}
	for(size_t i=0;i<a->dim;i++){
		if(a->shape[i]!=b->shape[i]){
			return 0;
		}
	}
	return !0;
}

int tensor_mul_hadamard(tensor_t**ret,const tensor_t*a,const tensor_t*b){
	if(!tensor_have_same_shape(a,b)){
		return !0;
	}
	int res;
	res=tensor_new_uninitialized(ret,a->shape,a->dim);
	if(res){
		return res;
	}
	size_t num_elements=tensor_num_elements(a);
	for(size_t i=0;i<num_elements;i++){
		(*ret)->elements[i]=a->elements[i]*b->elements[i];
	}
	return 0;
}

int tensor_add(tensor_t**ret,const tensor_t*a,const tensor_t*b){
	if(!tensor_have_same_shape(a,b)){
		return !0;
	}
	int res;
	res=tensor_new_uninitialized(ret,a->shape,a->dim);
	if(res){
		return res;
	}
	size_t num_elements=tensor_num_elements(a);
	for(size_t i=0;i<num_elements;i++){
		(*ret)->elements[i]=a->elements[i]+b->elements[i];
	}
	return 0;
}

int tensor_add_asign(tensor_t*self,const tensor_t*b){
	if(!tensor_have_same_shape(self,b)){
		return !0;
	}
	size_t num_elements=tensor_num_elements(self);
	for(size_t i=0;i<num_elements;i++){
		self->elements[i]+=b->elements[i];
	}
	return 0;
}

int tensor_from_vector_to_column_vector(tensor_t*self){
	if(self->dim!=1){
		return !0;
	}
	size_t*new_shape=realloc(self->shape,2*sizeof(*(self->shape)));
	if(!new_shape){
		return !0;
	}
	self->shape=new_shape;
	self->dim=2;
	self->shape[1]=self->shape[0];
	self->shape[0]=1;
	return 0;
}

int tensor_from_vector_to_row_vector(tensor_t*self){
	if(self->dim!=1){
		return !0;
	}
	size_t*new_shape=realloc(self->shape,2*sizeof(*(self->shape)));
	if(!new_shape){
		return !0;
	}
	self->shape=new_shape;
	self->dim=2;
	self->shape[1]=1;
	return 0;
}

int tensor_transpose(tensor_t*self,size_t dim1,size_t dim2){
	if((self->dim<=dim1)||(self->dim<=dim2)){
		return !0;
	}
	size_t tmp=self->shape[dim1];
	self->shape[dim1]=self->shape[dim2];
	self->shape[dim2]=tmp;
	return 0;
}

