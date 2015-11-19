#include<stdio.h>
#include <vector>
using namespace std;

vector <int> kakunou;

int a = 12345;
//int kakunou[100];

void func(int _a){
	kakunou.push_back(_a % 10);
	int tmp = _a;
	for (int i = 1;(tmp = tmp / 10) != 0; i++){
		kakunou.push_back(tmp % 10);
	}

	int size = kakunou.size() -1;
	for (int i = size; i >= 0; i--){
		printf("%d\n", kakunou[i]);
	}
}


void main(){
	func(a);
	getchar();
}