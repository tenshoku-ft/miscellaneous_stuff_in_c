#include <gmocoin.h>
#include <stdio.h>

int main(int argc,const char**argv,const char**envp){
	gmocoin_t*gmocoin;
	int res;
	res=gmocoin_new(&gmocoin);
	if(res){
		return !0;
	}
	gmocoin_status_t status;
	res=gmocoin_status(gmocoin,&status);
	if(res){
		return !0;
	}
	printf("status: ");
	switch(status){
	case GMOCOIN_STATUS_MAINTENANCE:
		printf("MAINTENANCE\n");
		break;
	case GMOCOIN_STATUS_PREOPEN:
		printf("PREOPEN\n");
		break;
	case GMOCOIN_STATUS_OPEN:
		printf("OPEN\n");
		break;
	default:
		printf("\n");
		break;
	}
	gmocoin_del(gmocoin);
	return 0;
}

