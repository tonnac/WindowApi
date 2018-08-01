#include "WindowClass.h"

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE pre, LPWSTR szCmdLine, int cmd)
{
	Window wd;

	wd.setWindow(hinst);
	wd.Run();

	return 0;
}