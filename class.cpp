#include<stdio.h>

class Character{
	float m_pos;
	void Move();
};

class Item{
	char* name;
};


class Player:Character{
	Item has_item;
};




int main(){
	return 0;
}