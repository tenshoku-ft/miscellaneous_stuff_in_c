#include "xorshift.h"
#include <math.h>
#include <stdlib.h>

struct random_xorshift128_st{
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t w;
};

void random_xorshift128_new(random_xorshift128_t**pself,uint32_t x,uint32_t y,uint32_t z,uint32_t w){
	*pself=malloc(sizeof(**pself));
	if(!*pself){
		return;
	}
	(*pself)->x=x;
	(*pself)->y=y;
	(*pself)->z=z;
	(*pself)->w=w;
}

uint32_t random_xorshift128_next_u32(random_xorshift128_t*self){
	uint32_t t;
	t=self->x^(self->x<<11);
	self->x=self->y;
	self->y=self->z;
	self->z=self->w;
	self->w=(self->w^(self->w>>19))^(t^(t>>8));
	return self->w;
}

float random_xorshift128_uniform_f32(random_xorshift128_t*self){
	uint32_t r=random_xorshift128_next_u32(self);
	return r/4294967295.f;
}

float random_xorshift128_uniform_between_f32(random_xorshift128_t*self,float a,float b){
	return a+random_xorshift128_uniform_f32(self)/(b-a);
}

float random_xorshift128_standard_normal_f32(random_xorshift128_t*self){
	float u1=random_xorshift128_uniform_f32(self);
	float u2=random_xorshift128_uniform_f32(self);
	return sqrtf(-2.f*logf(u1))*cosf(2*M_PI*u2);
}

float random_xorshift128_normal_f32(random_xorshift128_t*self,float mu,float sigma){
	return mu+sigma*random_xorshift128_standard_normal_f32(self);
}

