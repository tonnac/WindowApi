#include "Core.h"


class Sample : public Core
{
private:
	Bitmap m_bBitmap;
public:
	bool Init()
	{
		m_bBitmap.Init();
		m_bBitmap.LoadFile(L"86754.bmp");
		return true;
	}
	bool Frame()
	{
		if (I_Input.getKey('A') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.setOffset((-1)*g_fSecPerFrame * 300.0f, 0);
		}
		if (I_Input.getKey('D') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.setOffset((1)*g_fSecPerFrame * 300.0f, 0);
		}
		if (I_Input.getKey('W') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.setOffset(0, (-1)*g_fSecPerFrame * 300.0f);
		}
		if (I_Input.getKey('S') >= KEYSTATE::KEY_PUSH)
		{
			m_bBitmap.setOffset(0, (1)*g_fSecPerFrame * 300.0f);
		}
		m_bBitmap.Frame();
		return true;
	}
	bool Render()
	{
		static DWORD frame = 0;
		BITMAP bBmpInfo = m_bBitmap.getBmpInfo();
		HDC& hMemDC = m_bBitmap.getMemDC();
		Sleep(30);
		//BitBlt(g_hOffScreenDC, static_cast<int>(m_bBitmap.getPos()), static_cast<int>(m_bBitmap.getPos(1)), 48, 48, hMemDC, 1 * frame * 49, 201, SRCCOPY);
		BitBlt(g_hOffScreenDC, static_cast<int>(m_bBitmap.getPos()), static_cast<int>(m_bBitmap.getPos(1)), 48, 48, hMemDC, 1 + (frame * 49), 201, SRCAND);
	//	BitBlt(g_hOffScreenDC, static_cast<int>(m_bBitmap.getPos()), static_cast<int>(m_bBitmap.getPos(1)), 48, 48, hMemDC, 1 * frame * 49, 0, SRCPAINT);
		//	StretchBlt(g_hOffScreenDC, m_bBitmap.getPos(), m_bBitmap.getPos(1), 68, 79, hMemDC, 46, 62, 68, 79, SRCCOPY);
		frame = (++frame) % 11;
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