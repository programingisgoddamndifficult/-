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
	//分页处理
	int m_curPage=0; //当前页
	int m_maxPage = 1; //最大页数
	int m_extraData; //最后一页余数
	Operate();
	void run();
	int menu();//判断在菜单界面用户进行的操作
	int book();//判断在图鉴界面用户进行的操作(选择了哪个宝可梦)
	void book_sec();//判断“查看进化态”按钮状态
	void book_thr();//判断“放生”按钮状态
	void map_catch();//判断“捕捉”按钮状态
	void drawPageTurnButton();//图鉴翻页
	void info_boss();//判断“查看boss”按钮状态
	void check_bag();//计算目前所拥有的妖怪数量

	void initMeun();//初始化菜单、图鉴、背包（加载图片等）
	void initBook();
	void initBackPack();
	void initMap();
	void drawBackground();
	void ShowPlayerInfo();
	void ShowMap();
	void ShowElf();
	void ShowBoss();
	bool Timer(int ms);//定时器 捕捉时保证点击一次只进行一次捕捉

	void Search();//实现查找功能
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

