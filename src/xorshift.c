#include "xorshift.h"

struct random_xorshift128_st{
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t w;
};

void random_xorshift128_init(random_xorshift128_t*self,uint32_t x,uint32_t y,uint32_t z,uint32_t w){
	self->x=x;
	self->y=y;
	self->z=z;
	self->w=w;
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

