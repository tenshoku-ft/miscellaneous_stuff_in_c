#include <stdio.h>

#include "tensor.h"
#include "linear.h"
#include "activation.h"
#include "xorshift.h"

void print_tensor(tensor_t*t){
	printf("shape:");
	for(size_t i=0;i<t->dim;i++){
		printf(" %ld",t->shape[i]);
	}
	printf("\nelements:\n");
	size_t num_elements=tensor_num_elements(t);
	for(size_t i=0;i<num_elements;i++){
		printf(" %6e\n",t->elements[i]);
	}
}

int main(int argc,const char*const*argv,const char*const*envp){
	if(argc!=2){
		printf("Usage: %s parameters\n",argv[0]);
	}
	const char*params_filename=argv[1];
	random_xorshift128_t*random_state;
	FILE*fp;
	linear_t*l1;
	random_xorshift128_new(&random_state,123456789,362436069,521288629,88675123);
	if((fp=fopen(params_filename,"rb"))){
		linear_deserialize(&l1,fp);
		printf("input: %ld, output: %ld\nweight:\n",l1->in_features,l1->out_features);
		print_tensor(l1->weight);
		printf("bias:\n");
		print_tensor(l1->bias);
		linear_del(l1);
		fclose(fp);
	}else{
		if(!(fp=fopen(params_filename,"w+b"))){
			return !0;
		}
		linear_new_uninitialized(&l1,28*28,10);
		linear_init_xavier(l1,(float(*)(void*,float,float))random_xorshift128_normal_f32,random_state);
		linear_serialize(l1,fp);
		linear_del(l1);
		fclose(fp);
	}
}

