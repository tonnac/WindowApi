#include "Core.h"


class Sample : public Core
{
private:
	Bitmap m_bBitmap;
public:
	bool Init()
	{
		m_bBitmap.Init();
		
		return true;
	}
	bool Frame()
	{
		m_bBitmap.Frame();
		return true;
	}
	bool Render()
	{
		m_bBitmap.LoadFile(L"bitmap1.bmp");
		BitBlt(g_hOffScreenDC, 100, 100, 800, 600, m_bBitmap.m_hMemDC, 0, 0, SRCCOPY);
		m_bBitmap.Render();
		return true;
	}
	bool Release()
	{
		m_bBitmap.Release();
		return true;
	}
};


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR szCmdLine, int nCmdShow)
{
	Sample wd;
	wd.SetInstance(hInstance);
	wd.SetWindow();
	wd.Run();
	return 0;
}