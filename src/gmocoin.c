#include "gmocoin.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define GMOCOIN_URL_MAX_LENGTH 1024
#define GMOCOIN_ENDPOINT_PUBLIC "https://api.coin.z.com/public"

struct gmocoin_st{
	CURL*curl;
};

int gmocoin_new(gmocoin_t**pself){
	if(!pself){
		return !0;
	}
	*pself=malloc(sizeof(gmocoin_t));
	if(!*pself){
		return !0;
	}
	curl_global_init(CURL_GLOBAL_DEFAULT);
	(*pself)->curl=curl_easy_init();
	if(!((*pself)->curl)){
		free(*pself);
		*pself=NULL;
		return !0;
	}
	return 0;
}
typedef struct{
	void*ptr;
	size_t size;
}gmocoin_curl_callback_function_userdata_t;

static size_t gmocoin_curl_callback_function(void*ptr,size_t size,size_t nmemb,gmocoin_curl_callback_function_userdata_t*userdata){
	size_t total_size=size*nmemb;
	if(!(userdata->ptr=malloc(total_size))){
		return userdata->size=0;
	}
	memcpy(userdata->ptr,ptr,total_size);
	return userdata->size=total_size;
}

static int gmocoin_request_public(gmocoin_t*self,const char*method,const char*path,void*body,size_t body_length,void**content,size_t*content_length){
	char url[GMOCOIN_URL_MAX_LENGTH+1];
	strncpy(url,GMOCOIN_ENDPOINT_PUBLIC,GMOCOIN_URL_MAX_LENGTH);
	strncat(url,path,GMOCOIN_URL_MAX_LENGTH);
	curl_easy_setopt(self->curl,CURLOPT_URL,url);
	char method_get[]="GET";
	curl_easy_setopt(self->curl,CURLOPT_CUSTOMREQUEST,method);
	gmocoin_curl_callback_function_userdata_t response_body={0};
	curl_easy_setopt(self->curl,CURLOPT_WRITEFUNCTION,gmocoin_curl_callback_function);
	curl_easy_setopt(self->curl,CURLOPT_WRITEDATA,&response_body);
	curl_easy_setopt(self->curl,CURLOPT_CUSTOMREQUEST,method);
	if(!strncmp(method,method_get,GMOCOIN_URL_MAX_LENGTH)){
		curl_easy_setopt(self->curl,CURLOPT_POSTFIELDS,body);
		curl_easy_setopt(self->curl,CURLOPT_POSTFIELDSIZE,body_length);
	}
	CURLcode res=curl_easy_perform(self->curl);
	if(res!=CURLE_OK){
		return !0;
	}
	if(content){
		*content=response_body.ptr;
	}
	if(content_length){
		*content_length=response_body.size;
	}
	return 0;
}

int gmocoin_status(gmocoin_t*self,gmocoin_status_t*status){
	if(!status){
		return 0;
	}
	void*response_body;
	size_t response_body_size;
	int res;
	res=gmocoin_request_public(self,"GET","/v1/status",NULL,0,&response_body,&response_body_size);
	if(res){
		return !0;
	}
	cJSON*json=cJSON_ParseWithLength((const char*)response_body,response_body_size);
	free(response_body);
	cJSON*json_data;
	cJSON*json_data_status;
	if((!json)||(!cJSON_IsObject(json))){
		if(json){
			cJSON_free(json);
		}
		return !0;
	}
	json_data=cJSON_GetObjectItem(json,"data");
	if((!json_data)||(!cJSON_IsObject(json_data))){
		cJSON_free(json);
		return !0;
	}
	json_data_status=cJSON_GetObjectItem(json_data,"status");
	if((!json_data_status)||(!cJSON_IsString(json_data_status))){
		cJSON_free(json);
		return !0;
	}
	const char status_open[]="OPEN";
	const char status_preopen[]="PREOPEN";
	const char status_maintenance[]="MAINTENANCE";
	if(!strcmp(status_open,json_data_status->valuestring)){
		*status=GMOCOIN_STATUS_OPEN;
	}else if(!strcmp(status_preopen,json_data_status->valuestring)){
		*status=GMOCOIN_STATUS_PREOPEN;
	}else if(!strcmp(status_maintenance,json_data_status->valuestring)){
		*status=GMOCOIN_STATUS_MAINTENANCE;
	}
	cJSON_free(json);
	return 0;
}

void gmocoin_del(gmocoin_t*self){
	if(self->curl){
		curl_easy_cleanup(self->curl);
	}
}

