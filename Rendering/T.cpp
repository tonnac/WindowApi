#include "Core.h"
#include "BKObject.h"

class Sample : public Core
{
public:
	bool Init()
	{
		p1.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
		p2.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
		p3.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
		bk.LoadFile(L"BACKGROUND", L"../02_data/bmp/S1BK.bmp");
		p1.Set(291, 500, 10, 87, 25, 36);
		p2.Set(400, 500, 10, 87, 25, 36);
		p3.Set(100, 500, 10, 87, 25, 36);
		bk.Set(0, 0, 0, 0, 1600, 774);
		p1.Init();
		p2.Init();
		p3.Init();
		p2.setRendering(2.8f, LR_ROTATION);
		p3.setRendering(40.0f);
		bk.Init();
		return true;
	}
	bool Frame()
	{
		p1.Frame();
		p2.Frame();
		p3.Frame();
		bk.Frame();
		return true;
	}
	bool Render()
	{
		bk.Render();
		p1.Render();
		p2.Render();
		p3.Render();
		return true;
	}
	bool Release()
	{
		p1.Release();
		p2.Release();
		p3.Release();
		bk.Release();
		return true;
	}
private:
	Object		p1;
	Object		p2;
	Object		p3;
	BKObject	bk;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}