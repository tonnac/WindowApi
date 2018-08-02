#include "Core.h"

class Sample : public Core
{
private:
public:
	bool Init() override
	{
		return true;
	}
	bool Frame() override
	{
		return true;
	}
	bool Render() override
	{
		if (I_Input.getKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"LEFT", L"PUSH", MB_OK);
		}
		if (I_Input.m_dwCurrentMouse[0] == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"LEFTBUTTON", L"PUSH", MB_OK);
		}
		if (I_Input.m_dwCurrentMouse[0] == KEYSTATE::KEY_HOLD)
		{
			MessageBox(nullptr, L"LEFTBUTTON", L"HOLD", MB_OK);
		}
		return true;
	}
	bool Release() override
	{
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