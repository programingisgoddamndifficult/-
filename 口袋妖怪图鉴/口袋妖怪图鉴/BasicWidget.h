#pragma once
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {};
	int width();  //��ȡ���ڵĳ��Ϳ�
	int height();
	void setFixedSize(int w, int h);

	int x(); //��ȡ���������
	int y();
	void move(int x, int y);

	virtual void show() = 0;
protected:
	int m_y;
	int m_x;
	int m_w;
	int m_h;
};

