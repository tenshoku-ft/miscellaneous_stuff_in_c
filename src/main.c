#include <stdio.h>

#include "tensor.h"
#include "linear.h"
#include "activation.h"

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
	if(argc!=1){
		printf("Usage: %s\n",argv[0]);
	}
	tensor_t*orig;
	tensor_t*row;
	tensor_t*column;
	tensor_t*product;
	size_t shape_three=3;
	tensor_new_uninitialized(&orig,&shape_three,1);
	orig->elements[0]=1;
	orig->elements[1]=2;
	orig->elements[2]=3;
	tensor_dup(orig,&row);
	tensor_from_vector_to_row_vector(row);
	tensor_dup(orig,&column);
	tensor_from_vector_to_column_vector(column);
	tensor_del(orig);
	printf("row vector\n");
	print_tensor(row);
	printf("column vector\n");
	print_tensor(column);
	tensor_mul_matrix(&product,row,column);
	printf("product\n");
	print_tensor(product);
	tensor_del(product);
	tensor_mul_matrix(&product,column,row);
	printf("product\n");
	print_tensor(product);
	tensor_del(product);
	tensor_del(row);
	tensor_del(column);
}

