#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

int main(int argv, char*argc[]){
	//読み込みマップの縦横
	int width = 78;
	int height = 14;

	char buff[256];
	int num;
	FILE *pFile = 
		fopen(
		"map.csv",
		"r"
		);

	assert(pFile != NULL);

	int *_p = (int*)malloc(sizeof(int)*width*height);

	for (int i = 0; i < width*height; i++){
		if (fscanf(pFile, "%d", &num) != NULL){
			_p[i] = num;
			fscanf(pFile, "%1s", buff);
		}
		else{
			return -1;
		}
	}

	for (int i = 0; i < width*height; i++){
		if ((i+1)%width == 0){
			printf("%d\n",_p[i]);
		}
		else{
			printf("%d", _p[i]);
		}
	}
	getchar();
	free(_p);
	return 0;
}