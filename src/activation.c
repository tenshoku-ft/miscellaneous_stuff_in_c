#include "activation.h"

#include <math.h>

float softsign_float(float x){
	return x/(1.0f+fabsf(x));
}

float softsign_float_derivative(float x){
	float a=1.0f+fabsf(x);
	return 1.0f/a/a;
}


