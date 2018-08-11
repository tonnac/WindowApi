#include "RotationObject.h"
#include "Bitmap.h"

HDC						g_hScreenDC;
HDC						g_hOffScreenDC;

class Sample : public Core
{
private:
	RotationObject  m_rObj;
	HBRUSH			m_bkBrush;
public:
	bool		Init() override
	{
		g_hScreenDC = GetDC(g_hWnd);
		g_hOffScreenDC = CreateCompatibleDC(g_hScreenDC);
		HBITMAP off = CreateCompatibleBitmap(g_hScreenDC, m_rtClient.right, m_rtClient.bottom);
		SelectObject(g_hOffScreenDC, off);
		m_bkBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(g_hOffScreenDC,m_bkBrush);
		m_rObj.Init();
		
		return true;
	}
	bool		Frame() override
	{
		m_rObj.Frame();
		return true;
	}
	bool		Render() override
	{
		PatBlt(g_hOffScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, PATCOPY);
		m_rObj.Render();
		BitBlt(g_hScreenDC, 0, 0, m_rtClient.right,m_rtClient.bottom, g_hOffScreenDC, 0, 0, SRCCOPY);
		return true;
	}
	bool		Release() override
	{
		DeleteObject(m_bkBrush);
		DeleteDC(m_hOffScreenDC);
		ReleaseDC(g_hWnd, m_hScreenDC);
		m_rObj.Release();
		return true;
	}
public:
	Sample (HINSTANCE a, LONG b,LONG c) : Core(a,b,c)
	{}
private:
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmeShow)
{
	Sample wd(hinst, 800, 600);
	wd.SetWindow();
	wd.Run();

	return 0;
}