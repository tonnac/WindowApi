#pragma once
#include <windows.h>
#include <tchar.h>

#pragma comment(lib,"winmm.lib")

enum class KEYSTATE {
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};

template <class K>
class Singleton
{
protected:
	Singleton() {}
public:
	static K& getInstance()
	{
		static K inst;
		return inst;
	}
};



extern HWND g_hWnd;