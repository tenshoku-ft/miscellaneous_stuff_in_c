#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif // #ifdef __cplusplus

typedef struct gmocoin_st gmocoin_t;

typedef enum {
	GMOCOIN_STATUS_MAINTENANCE,
	GMOCOIN_STATUS_PREOPEN,
	GMOCOIN_STATUS_OPEN,
} gmocoin_status_t;

typedef struct {
	char price[80];
	char side[8];
	char size[80];
	char timestamp[32];
} gmocoin_trade_t;

int gmocoin_new(gmocoin_t**);
int gmocoin_status(gmocoin_t*,gmocoin_status_t*);
int gmocoin_trades(gmocoin_t*,const char*,int,int,gmocoin_trade_t**,size_t*);
void gmocoin_del(gmocoin_t*);

#ifdef __cplusplus
} // extern "C"{
#endif // #ifdef __cplusplus

