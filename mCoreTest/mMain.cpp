#include "Sample.h"
#include "Sprite.h"
#include "RObject.h"

class Pl : public Core
{
public:
	bool Init()
	{
		bk.LoadFile(L"BG", L"../02_data/BKBmp.bmp");
		bk.Set(g_rtClient.right / 2,g_rtClient.bottom /2 , 0, 0, 600, 240);
		bk.Init();
		for (int i = 0; i < 3; ++i)
		{
			d[i].LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
			d[i].Set(rand() % 400 + 200, rand() % 400, 50, 75, 48, 48);
			d[i].Init();
			d[i].isRotate = true;
		}
		d[0].Set(600, 200, 50, 75, 48, 48);
		d[0].SetInverse(LR_ROTATION, 2.6f);
	//	d[1].Set(500, 300, 50, 74, 48, 48);
//		d[2].SetInverse(LR_ROTATION, 2.8f);
		//a.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
		//a.Set(500, 500, 50, 74, 48, 48);
		//a.Init();
		//a.SetInverse(0, 2.0f);
		int l, t, r, b;
		int total, temp;
		std::ifstream in("SPRITE.txt",std::ios::in);
		std::string ee;
		std::string stemp;
		if (in.is_open())
		{
			while (!in.eof())
			{
				std::getline(in, ee);
				std::istringstream(ee) >> stemp >> total;
				for (int i = 0; i < 1; ++i)
				{
					e.LoadFile(L"PLAYER", L"../02_data/KahoColor.bmp", L"../02_data/KahoMask.bmp");
					e.Set(200, 200);
					std::getline(in, ee);
					std::istringstream(ee) >> stemp >> temp;
					for (int j = 0; j < temp; ++j)
					{
						RECT rt;
						std::getline(in, ee);
						std::istringstream(ee) >> l >> t >> r >> b;
						rt.left = l;
						rt.top = t;
						rt.right = r;
						rt.bottom = b;
						e.m_spritelist.push_back(rt);
					}
				}
				break;
			}
		}
		else
		{
			MessageBox(nullptr, L"X", L"X", MB_OK);
		}

		e.Init();
//		a.Init();
		return true;
	}
	bool Frame()
	{
		bk.Frame();
		e.Frame();
		for (int i = 0; i < 3; ++i)
		{
			d[i].Frame();
		}
//		a.Frame();
		return true;
	}
	bool Render()
	{
		bk.Render();
		e.Render();
		for (int i = 0; i < 3; ++i)
		{
			d[i].Render();
		}
//		a.Render();
		return true;
	}
	bool Release()
	{
		bk.Release();
		e.Release();
		for (int i = 0; i < 3; ++i)
		{
			d[i].Release();
		}
//		a.Release();
		return true;
	}
private:
	Object d[3];
	Sprite e;
	Player a;
	BKObject bk;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Pl wd;
	wd.SetWindow(hinst, 1024, 700);
	wd.Run();

	return 0;
}