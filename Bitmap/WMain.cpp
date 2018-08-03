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
		if (m_Input.getKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"qwe", L"LEFT", MB_OK);
		}
		if (m_Input.getKey(VK_RIGHT) == KEYSTATE::KEY_HOLD)
		{
			MessageBox(nullptr, L"qwe", L"RIGHT", MB_OK);
		}
		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()
	{
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