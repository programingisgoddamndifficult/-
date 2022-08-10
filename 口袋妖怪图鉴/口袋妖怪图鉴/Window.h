#pragma once
//界面切换准备文件
#include"necessaryFile.h"
using namespace std;
class Window
{
public:
	Window(int width, int height, int flag);
	//阻塞窗口
	int exec();

	static int Width();
	static int Height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	inline static bool hasMsg() 
	{return peekmessage(&m_msg, EM_MOUSE | EM_KEY);}
	inline static ExMessage& getMsg()
	{return m_msg;}
private:
	//H-handle WND-window
	//窗口句柄 句柄是由操作环境定义的一个唯一的整数值，它被程序用来标识或者切换到对象，如窗体或控件等。
	HWND m_handle; 
	//ExMessage为用于保存鼠标消息的结构体
	inline static ExMessage m_msg; 
};

