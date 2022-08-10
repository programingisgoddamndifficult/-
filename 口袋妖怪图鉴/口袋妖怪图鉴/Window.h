#pragma once
//�����л�׼���ļ�
#include"necessaryFile.h"
using namespace std;
class Window
{
public:
	Window(int width, int height, int flag);
	//��������
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
	//���ھ�� ������ɲ������������һ��Ψһ������ֵ����������������ʶ�����л��������細���ؼ��ȡ�
	HWND m_handle; 
	//ExMessageΪ���ڱ��������Ϣ�Ľṹ��
	inline static ExMessage m_msg; 
};

