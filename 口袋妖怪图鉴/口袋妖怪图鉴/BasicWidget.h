#pragma once
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {};
	int width();  //获取窗口的长和宽
	int height();
	void setFixedSize(int w, int h);

	int x(); //获取物体的坐标
	int y();
	void move(int x, int y);

	virtual void show() = 0;
protected:
	int m_y;
	int m_x;
	int m_w;
	int m_h;
};

