#include"necessaryFile.h"
#include"Window.h"
#include"Operate.h"
using namespace std;
int main()
{
	Window mainw(960, 640,EW_SHOWCONSOLE);
	Operate m;
	m.run();

	return mainw.exec();
}