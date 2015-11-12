#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

int main(int argv, char*argc[]){
	//ì«Ç›çûÇ›É}ÉbÉvÇÃècâ°
	int width = 78;
	int height = 14;

	char buff[256];
	FILE *pFile = 
		fopen(
		"map.csv",
		"r"
		);

	assert(pFile != NULL);

	int *_p = (int*)malloc(sizeof(int)*width*height);

	for (int i = 0; i < width*height; i++){
		if (fscanf(pFile, "%1s", buff) != NULL){
			if (strcmp(buff, ",") == 0){
				_p[i] = 0;
				continue;
			}
			else{
				//_p[i] = (int)buff;
				_p[i] = 1;
				fscanf(pFile, "%1s", buff);
			}
		}
		else{
			return -1;
		}
	}

	for (int i = 0; i < width*height; i++){
		if (i%width == 0){
			printf("%d\n",_p[i]);
		}
		else{
			printf("%d", _p[i]);
		}
	}
	getchar();
	return 0;
}