#pragma once
#include"Window.h"
#include<vector>
#include"PushButton.h"
#include"necessaryFile.h"
#include"Backpack.h"
using namespace std;

class Operate
{
	enum Operator
	{
		Menu,
		Map,
		PlayerInfo,
		Elf,
		SEARCH,
		BOSS
	};
public:
	int op;
	int temp;
	int flag;
	int ca;
	int catch_flag = 0;
	int boss_flag = 0;
	int boss_index;
	int t_width = 15;
	int t_height = 30;
	//��ҳ����
	int m_curPage=0; //��ǰҳ
	int m_maxPage = 1; //���ҳ��
	int m_extraData; //���һҳ����
	Operate();
	void run();
	int menu();//�ж��ڲ˵������û����еĲ���
	int book();//�ж���ͼ�������û����еĲ���(ѡ�����ĸ�������)
	void book_sec();//�жϡ��鿴����̬����ť״̬
	void book_thr();//�жϡ���������ť״̬
	void map_catch();//�жϡ���׽����ť״̬
	void drawPageTurnButton();//ͼ����ҳ
	void info_boss();//�жϡ��鿴boss����ť״̬
	void check_bag();//����Ŀǰ��ӵ�е���������

	void initMeun();//��ʼ���˵���ͼ��������������ͼƬ�ȣ�
	void initBook();
	void initBackPack();
	void initMap();
	void drawBackground();
	void ShowPlayerInfo();
	void ShowMap();
	void ShowElf();
	void ShowBoss();
	bool Timer(int ms);//��ʱ�� ��׽ʱ��֤���һ��ֻ����һ�β�׽

	void Search();//ʵ�ֲ��ҹ���
private:
	IMAGE bk, bookbk, backPack_bk, map_bk;
	ExMessage m_msg, b_msg;
	vector<PushButton*> menu_btns;
	vector<PushButton*> book_btns;
	vector<Monster*> elf;
	vector<Evolve*> evolved;
	vector<PushButton*> book_btns_sec;
	vector<PushButton*> book_btns_thr;
	vector<PushButton*> boss_btns;
	vector<Boss*> boss;
	PushButton* m_prevBtn;
	PushButton* m_nextBtn;
	PushButton* m_catch;
	PushButton* m_boss;
	Player me;
};

