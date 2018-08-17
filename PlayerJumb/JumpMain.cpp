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
		bk.Set(0, 0, 0, 0, 1600, 774);
		bk.Init();

		TerrainObject * t1 = New TerrainObject;
		t1->Set(1, 620, 1, 620, 1250, 154);
		bk.AddTerrain(t1);

		t1 = New TerrainObject;
		t1->Set(1251, 565, 1251, 565, 103, 212);
		bk.AddTerrain(t1);

		t1 = New TerrainObject;
		t1->Set(1354, 465, 1354, 465, 131, 380);
		bk.AddTerrain(t1);

		t1 = New TerrainObject;
		t1->Set(1485, 621, 1485, 621, 115, 153);
		bk.AddTerrain(t1);

		p2.Set(130, 540, 10, 87, 25, 36);
		p2.Init();
		p2.setRendering(2.8f, INVERSE::DEFAULT);

		Scroll1.Init();

		return true;
	}
	bool Frame()
	{
		bk.Collision(&p2);
		p2.Frame();
		Scroll1.Frame();

		return true;
	}
	bool Render()
	{
		bk.Render();
		p2.Render();
		Scroll1.Render();
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
	Scroll		Scroll1;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}