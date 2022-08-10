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
	//判断鼠标是否在当前按钮上
	//判断鼠标是否点击按钮
	bool isIn();
	bool isClicked();

	void changeColor(const ExMessage& msg);
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);
	void changeText(string x);//修改按钮文字
private:
	string m_text;//按钮上的文字
	ExMessage m_msg;
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = RED;
};

