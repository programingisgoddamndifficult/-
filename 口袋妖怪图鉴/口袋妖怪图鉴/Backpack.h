#pragma once
#include"necessaryFile.h"
using namespace std;
class info
{
public:
    string name="С��";
	int level =  10;
};
class Player :public info
{
public:
	Player(string n){name = n;}
	Player() {};
	string bag[25];
	int ba = 0;//��������Ʒ����
};

class Monster:public info
{

public:
	IMAGE img;
	string feature = "һ��";//����
	long number;
	int level;
	char condition = 'N';//״̬ ��ӵ��Y or Ұ��N��
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
	double rate;//�������
	Boss(string n, string x, double r) { name = n; feature = x; rate = r; condition = 'N'; }
};



