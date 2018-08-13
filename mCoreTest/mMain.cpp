#include "Sample.h"
#include "Sprite.h"
#include "GroundObject.h"

class Pl : public Core
{
public:
	Pl()
	{
		g = new GroundObject(&a);
	}
	bool Init()
	{
		bk.LoadFile(L"BG", L"../02_data/BKBmp.bmp");
		bk.Set(0 ,0 , 289, 0, 609, 239);
		bk.Init();
		g->Set(0, 0, 289, 181, 1500, 239);
		g->Init();

		a.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
		a.Set(291, 500, 50, 75, 48, 48);
		a.Init();
		a.SetInverse(0, 2.8f);

		return true;
	}
	bool Frame()
	{
		RECT r = a.getCollisionRt();
		RECT t = g->getCollisionRt();
		if (Collision::RectInRect(r, t))
		{
			RECT d;
			d = { 1,2,3,4 };
		}
		else
		{
			a.m_CenterPos.y += g_fPerSecFrame * 100.0f;
		}
		bk.Frame();
		a.Frame();
		g->Frame();
		return true;
	}
	bool Render()
	{
		bk.Render();
		a.Render();
		g->Render();
		return true;
	}
	bool Release()
	{
		bk.Release();
		a.Release();
		return true;
	}
private:
	Player a;
	BKObject bk;
	GroundObject * g;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Pl wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}