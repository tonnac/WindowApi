#include "Core.h"
#include "BKObject.h"
#include "SpriteMgr.h"
#include "Player.h"

class Sample : public Core
{
public:
	bool Init()
	{
		S_SpriteMgr.SpriteSet(L"Kaho.txt");
		p1.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
		bk.LoadFile(L"BACKGROUNG", L"../02_data/S1BK.bmp");
		m_Player.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
		m_Player.Set(400, 550, 10, 87, 25, 36);
		p1.Set(291, 500, 10, 87, 25, 36);
		bk.Set(0, 0, 0, 0, 1600, 774);
		p1.Init();
		bk.Init();
		m_Player.Init();
		return true;
	}
	bool Frame()
	{
		p1.Frame();
		bk.Frame();
		m_Player.Frame();
		return true;
	}
	bool Render()
	{
		bk.Render();
		p1.Render();
		m_Player.Render();
		return true;
	}
	bool Release()
	{
		p1.Release();
		bk.Release();
		m_Player.Release();
		return true;
	}
private:
	Object		p1;
	BKObject	bk;
	Object		m_Player;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}