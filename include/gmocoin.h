#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct gmocoin_st gmocoin_t;

typedef enum {
	GMOCOIN_STATUS_MAINTENANCE,
	GMOCOIN_STATUS_PREOPEN,
	GMOCOIN_STATUS_OPEN,
} gmocoin_status_t;

int gmocoin_new(gmocoin_t**);
int gmocoin_status(gmocoin_t*,gmocoin_status_t*);
void gmocoin_del(gmocoin_t*);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

