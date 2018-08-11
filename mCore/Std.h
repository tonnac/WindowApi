#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <string>
#include <list>
#include <map>
#include <cstdlib>
#include <ctime>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"11_mCore.lib")

struct MEMINFO
{
	std::string  filename;
	int			 line;
	DWORD		 dwAllocateTime;
	void*		 addr;
};

using T_STR = std::basic_string<TCHAR>;
using MEM_MAP = std::map<void *, MEMINFO>;

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
	Singleton() {};
public:
	static K& getInstance()
	{
		static K inst;
		return inst;
	}
};

struct FloatPoint
{
	float x, y;
};


extern HWND					g_hWnd;
extern HINSTANCE            g_hInstance;
extern HDC					g_hOffScreenDC;
extern RECT					g_rtClient;
extern float				g_fPerSecFrame;

extern int					g_iNewCount;
extern MEM_MAP				MemoryMap;