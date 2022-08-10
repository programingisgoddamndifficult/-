#include "PushButton.h"

PushButton::PushButton(const string & text, int x, int y, int w, int h):BasicWidget(x, y, w, h), m_text(text)
{
}

void PushButton::show()
{
	setfillcolor(normal_c);
	setlinecolor(BLACK);
	::fillrectangle(m_x, m_y, m_x + m_w, m_y + m_h);

	//把文字居中显示在按钮中间
	settextcolor(BLACK);
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

bool PushButton::isIn()
{
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y < m_y + m_h)
	{
		return true;
	}
   return false;
}

bool PushButton::isClicked()
{
	if (isIn())
	{
		if (m_msg.message == WM_LBUTTONDOWN)
			return true;
	}
    return false;
}

void PushButton::changeColor(const ExMessage & msg)
{
	m_msg = msg;
	//如果鼠标不在按钮上
	if (isIn())
	{
		normal_c = hover_c;
	}
	else
		normal_c = WHITE;
		/*normal_c= RGB(232, 232, 236);*/
}

void PushButton::setBackgroundColor(COLORREF c)
{
	normal_c = c;
}

void PushButton::setHoverColor(COLORREF c)
{
	hover_c = c;
}

void PushButton::changeText(string x)
{
	m_text = x;
}
