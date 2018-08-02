#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <map>
#include <list>
#include <assert.h>

using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t>;
using T_STR = std::basic_string<TCHAR>;

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
extern HINSTANCE g_hInstance;
extern float g_fSecPerFrame;