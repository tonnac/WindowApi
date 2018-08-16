#include "Core.h"
#include "BKObject.h"
#include "SpriteMgr.h"
#include "Player.h"
#include "Scroll.h"
#include "TerrainObject.h"

class Sample : public Core
{
public:
	Sample() : Scroll1(&p2, &bk)
	{}
public:
	bool Init()
	{
		S_SpriteMgr.SpriteSet(L"../02_data/txt/Kaho.txt");
		p2.LoadFile(L"PLAYER", L"../02_data/bmp/KahoColor.bmp", L"../02_data/bmp/KahoMask.bmp");
		bk.LoadFile(L"BACKGROUND", L"../02_data/bmp/S1BK.bmp");

		tobject[0].Set(1, 620, 1, 620, 1250, 154);
		tobject[1].Set(1, 1, 1, 1, 1, 1);
		p2.Set(130, 540, 10, 87, 25, 36);
		bk.Set(0, 0, 0, 0, 1600, 774);
		p2.Init();
		tobject[1].Init();
		tobject[0].Init();
		p2.setRendering(2.8f, INVERSE::DEFAULT);
		bk.Init();
		Scroll1.Init();

		return true;
	}
	bool Frame()
	{
		for (int i = 0; i < 2; ++i)
		{
			tobject[i].Collision(&p2);
		}
		Scroll1.Frame();
		tobject[1].Frame();
		tobject[0].Frame();
		p2.Frame();
		bk.Frame();

		return true;
	}
	bool Render()
	{
		bk.Render();
		p2.Render();
		tobject[1].Render();
		tobject[0].Render();
		Scroll1.Render();
		return true;
	}
	bool Release()
	{
		p2.Release();
		bk.Release();
		tobject[0].Release();
		return true;
	}
private:
	Player		p2;
	BKObject	bk;
	Scroll		Scroll1;
	TerrainObject tobject[2];
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}