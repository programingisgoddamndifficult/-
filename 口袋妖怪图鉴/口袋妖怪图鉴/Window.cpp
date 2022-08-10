#include "Window.h"

Window::Window(int width, int height, int flag)
{
	m_handle = initgraph(width, height, flag);
	setbkmode(TRANSPARENT);
}


int Window::exec()
{
	return getchar();
}

int Window::Width()
{
	return getwidth();
}

int Window::Height()
{
	return getheight();
}

void Window::clear()
{
	cleardevice();
}

void Window::beginDraw()
{
	BeginBatchDraw();
}

void Window::flushDraw()
{
	FlushBatchDraw();
}

void Window::endDraw()
{
	EndBatchDraw();
}
