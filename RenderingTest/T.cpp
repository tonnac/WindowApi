#include "Core.h"
#include "Object.h"

class Sample : public Core
{
public:
	bool Init()
	{
		p1.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
		p1.Set(291, 500, 50, 75, 48, 48);
		p1.Init();
		return true;
	}
	bool Frame()
	{
		p1.Frame();
		return true;
	}
	bool Render()
	{
		p1.Render();
		return true;
	}
	bool Release()
	{
		p1.Release();
		return true;
	}
private:
	Object p1;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}