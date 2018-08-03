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

#pragma comment(lib,"winmm.lib")

extern HWND g_hWnd;