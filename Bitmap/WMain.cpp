#include "Core.h"

class Sample : public Core
{
private:
public:
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		if (I_Input.getKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"LEFT", L"PUSH", MB_OK);
		}
		return true;
	}
	bool Release()
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