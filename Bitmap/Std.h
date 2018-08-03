#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>

enum class KEYSTATE
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};

template <typename K>
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

#pragma comment(lib,"winmm.lib")

extern HWND g_hWnd;