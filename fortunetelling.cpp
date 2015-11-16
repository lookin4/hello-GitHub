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
		printf("      おみくじ占い～The Fortunetelling☆彡～\n\n名前[半角英数8文字]を入力してEnterキーを押してね！\n\n");
		for (int i = 0; i < 9; i++){
			a[i] = getchar();
			c = i;
			if (a[i] == '\n')
				break;
		};
		a[c] = '\0';
		printf("\n%sの%d/%dの運勢は", a, local->tm_mon + 1, local->tm_mday);
		if (!(strcmp(a, "Jreaper")) || !(strcmp(a, "jreaper"))){
			printf("最悪です。もう人生あきらめたほうがいいでしょう。\n乙乙。。。。。。。。。。。。。。ｗｗｗｗｗｗｗｗｗｗｗｗｗｗｗｗｗｗ");
		}
		else{
			int total = (local->tm_mon + 11) * local->tm_mday;
			for (int i = 0; i < c; i++){
				total += a[i];
			}
			std::string str[6] = {
				"大吉です！！",
				"中吉です！",
				"小吉です。",
				"吉です。",
				"凶です・・",
				"大凶です・・・・・・・"
			};
			printf("%s",str[total % 6].c_str() );
		}
		_getch();
	}
	return 0;
}