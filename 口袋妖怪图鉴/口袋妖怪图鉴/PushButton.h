#pragma once
#include "BasicWidget.h"
#include "necessaryFile.h"
using namespace std;
class PushButton :
	public BasicWidget
{
public:
	PushButton(const string& text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);
	void show() override;
	//�ж�����Ƿ��ڵ�ǰ��ť��
	//�ж�����Ƿ�����ť
	bool isIn();
	bool isClicked();

	void changeColor(const ExMessage& msg);
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);
	void changeText(string x);//�޸İ�ť����
private:
	string m_text;//��ť�ϵ�����
	ExMessage m_msg;
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = RED;
};

