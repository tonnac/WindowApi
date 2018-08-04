#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <string>

#pragma comment(lib,"winmm.lib")

using T_STR = std::basic_string<TCHAR>;

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


extern HWND					g_hWnd;				//Timer::Render()
extern HINSTANCE			g_hInstance;		//Bitmap::LoadFile() 
extern HDC					g_hOffScreenDC;		//Timer::Render()
extern float				g_fSecPerFrame;		//Sample::Frame()
