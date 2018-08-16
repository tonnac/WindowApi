#include "Core.h"
#include "BKObject.h"
#include "SpriteMgr.h"
#include "Player.h"
#include "ScrollObject.h"

class Sample : public Core
{
public:
	bool Init()
	{
		S_SpriteMgr.SpriteSet(L"../02_data/txt/Kaho.txt");
		p2.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
		bk.LoadFile(L"BACKGROUND", L"../02_data/bmp/S1BK.bmp");
		Scroll.Init();
		p2.Set(400, 500, 10, 87, 25, 36);
		bk.Set(0, 0, 0, 0, 1600, 774);
		p2.Init();
		p2.setRendering(2.8f, INVERSE::DEFAULT);
		bk.Init();
		return true;
	}
	bool Frame()
	{
		switch (Scroll.Collision(p2.getCollisionRt()))
		{
		case 1:
			bk.MoveScroll(100);
			break;
		case 2:
			bk.MoveScroll(-100);
			break;
		default:
			break;
		}
		
		Scroll.Frame();
		p2.Frame();
		bk.Frame();
		return true;
	}
	bool Render()
	{
		bk.Render();
		p2.Render();
		Scroll.Render();
		return true;
	}
	bool Release()
	{
		p2.Release();
		bk.Release();
		return true;
	}
private:
	Player		p2;
	BKObject	bk;
	ScrollObject	Scroll;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}