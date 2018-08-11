#include "Core.h"
#include "NPC.h"
#include "BitmapMgr.h"
#include "BKObject.h"

int iNPc = 10;

class Sample : public Core
{
	BKObject bkobj;
	Object  pObj;
	NPC		n1[10];
public:
	bool					Init()
	{
		for (int i = 0; i < iNPc; i++)
		{
			n1[i].Init();
			n1[i].LoadFile(L"NPC", L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
			n1[i].Set(rand() % 100 + 200, rand() % 100 + 200, 115, 62, 36, 35);
		}
		bkobj.Init();
		bkobj.LoadFile(L"BACKGROUND", L"../02_data/bk.bmp");
		bkobj.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
		pObj.Init();
		pObj.LoadFile(L"PLAYER", L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
		pObj.Set(500, 500, 133, 1, 42, 59);
		pObj.SetInverse(TB_ROTATION);
		return true;
	}
	bool					Frame()
	{
		bkobj.Frame();
		pObj.Frame();
		for (int i = 0; i < iNPc; i++)
		{
			n1[i].Frame();
		}
		return true;
	}
	bool					Render()
	{
		bkobj.Render();
		pObj.Render();
		for (int i = 0; i < iNPc; i++)
		{
			n1[i].Render();
		}
		return true;
	}
	bool					Release()
	{
		bkobj.Release();
		pObj.Release();
		for (int i = 0; i < iNPc; i++)
		{
			n1[i].Release();
		}
		return true;
	}
private:
};


int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}