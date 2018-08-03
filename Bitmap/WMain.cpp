#include "Core.h"

class Sample : public Core
{
//	Bitmap m_bitMap;
private:
public:
	bool Init() override
	{
//		m_bitMap.Init();
//		m_bitMap.LoadFile(L"bitmap1.bmp");
		return true;
	}
	bool Frame() override
	{
		//float m_fSpeed = 100;
		//if (I_Input.getKey('W') == KEYSTATE::KEY_PUSH)
		//{
		//	m_bitMap.SetOffset(0, -1 * g_fSecPerFrame * m_fSpeed);
		//}
		//if (I_Input.getKey('S') == KEYSTATE::KEY_PUSH)
		//{
		//	m_bitMap.SetOffset(0, 1 * g_fSecPerFrame * m_fSpeed);
		//}
		//if (I_Input.getKey('A') == KEYSTATE::KEY_PUSH)
		//{
		//	m_bitMap.SetOffset(-1 * g_fSecPerFrame * m_fSpeed, 0);
		//}
		//if (I_Input.getKey('D') == KEYSTATE::KEY_PUSH)
		//{
		//	m_bitMap.SetOffset(1 * g_fSecPerFrame * m_fSpeed, 0);
		//}
		//m_bitMap.Frame();
		return true;
	}
	bool Render() override
	{
//		m_bitMap.Render();
		return true;
	}
	bool Release() override
	{
//		m_bitMap.Release();
		return true;
	}
};



int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE preinst, LPWSTR szCmdLine, int Cmd)
{
	Sample wd;
	wd.setWindow(hinst);
	wd.Run();

	return 0;
}