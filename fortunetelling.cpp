#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<string>
#include <time.h>

int main(int argv, char*argc[]){
	while (1){
		system("cls");
		time_t timer;
		struct tm *local;
		timer = time(NULL);
		local = localtime(&timer);
		int c = 0;
		char a[9];
		printf("      ���݂����肢�`The Fortunetelling���c�`\n\n���O[���p�p��8����]����͂���Enter�L�[�������ĂˁI\n\n");
		for (int i = 0; i < 9; i++){
			a[i] = getchar();
			c = i;
			if (a[i] == '\n')
				break;
		};
		a[c] = '\0';
		printf("\n%s��%d/%d�̉^����", a, local->tm_mon + 1, local->tm_mday);
		if (!(strcmp(a, "Jreaper")) || !(strcmp(a, "jreaper"))){
			printf("�ň��ł��B�����l��������߂��ق��������ł��傤�B\n�����B�B�B�B�B�B�B�B�B�B�B�B�B�B������������������������������������");
		}
		else{
			int total = (local->tm_mon + 11) * local->tm_mday;
			for (int i = 0; i < c; i++){
				total += a[i];
			}
			std::string str[6] = {
				"��g�ł��I�I",
				"���g�ł��I",
				"���g�ł��B",
				"�g�ł��B",
				"���ł��E�E",
				"�勥�ł��E�E�E�E�E�E�E"
			};
			printf("%s",str[total % 6].c_str() );
		}
		_getch();
	}
	return 0;
}