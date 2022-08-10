#pragma once
#include"necessaryFile.h"
using namespace std;
class info
{
public:
    string name="小智";
	int level =  10;
};
class Player :public info
{
public:
	Player(string n){name = n;}
	Player() {};
	string bag[25];
	int ba = 0;//背包中物品个数
};

class Monster:public info
{

public:
	IMAGE img;
	string feature = "一般";//属性
	long number;
	int level;
	char condition = 'N';//状态 “拥有Y or 野生N”
	Monster(string n);
	Monster();
	Monster(string n, string x);
};
class Evolve :public Monster
{
public:
	Evolve(string n) { name = n; }
	Evolve(string n, string x) {name = n, feature = x; }
	IMAGE img;
};


class Boss :public Monster
{
public:
	double rate;//捕获机率
	Boss(string n, string x, double r) { name = n; feature = x; rate = r; condition = 'N'; }
};



