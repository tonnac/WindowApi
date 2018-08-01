#include "WindowClass.h"

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE prev, LPWSTR szCmdLine, int cmd)
{
	Window wd;
	wd.setWindow(hinst);
	wd.Run();

	return 0;
}