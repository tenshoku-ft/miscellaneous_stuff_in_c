#include <gmocoin.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,const char**argv,const char**envp){
	gmocoin_t*gmocoin;
	int res;
	if(argc!=4){
		printf("Usage: %s symbol page count\n",argv[0]);
		return !0;
	}
	res=gmocoin_new(&gmocoin);
	if(res){
		return !0;
	}
	gmocoin_trade_t*trades;
	size_t num_trades=0;
	res=gmocoin_trades(gmocoin,argv[1],atoi(argv[2]),atoi(argv[3]),&trades,&num_trades);
	if(res){
		return !0;
	}
	for(int i=0;i<num_trades;i++){
		printf("%-10s %-4s %-10s %s\n",trades[i].price,trades[i].side,trades[i].size,trades[i].timestamp);
	}
	free(trades);
	gmocoin_del(gmocoin);
	return 0;
}

