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
		if (I_Input.getKey('A') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.m_kPos.x += (-1)*g_fSecPerFrame * 300.0f;
		}
		if (I_Input.getKey('D') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.m_kPos.x += (1)*g_fSecPerFrame*300.0f;
		}
		if (I_Input.getKey('W') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.m_kPos.y += (-1)*g_fSecPerFrame*300.0f;
		}
		if (I_Input.getKey('S') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.m_kPos.y += (1)*g_fSecPerFrame*300.0f;
		}
		m_bBitmap.Frame();
		return true;
	}
	bool Render()
	{
		HDC hdc = GetDC(g_hWnd);
		m_bBitmap.LoadFile(L"bitmap1.bmp");
		BitBlt(g_hOffScreenDC,m_bBitmap.m_kPos.x,m_bBitmap.m_kPos.y,m_bBitmap.m_bBmpInfo.bmWidth,m_bBitmap.m_bBmpInfo.bmHeight,m_bBitmap.m_hMemDC,0,0,SRCCOPY);
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