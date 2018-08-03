#include "WindowClass.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR szCmdLine, int nCmdShow)
{
	Window wd(hInstance);
	wd.Init();
	wd.Frame();
	wd.Redner();
	wd.Release();
	return 0;
}