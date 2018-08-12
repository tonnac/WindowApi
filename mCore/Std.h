#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <fstream>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"11_mCore.lib")

#define New new(__FILE__,__LINE__)
#define PI 3.141592
#define DegreeToRadian(x) (x) * PI / 180.0f

struct MEMINFO
{
	std::string  filename;
	int			 line;
	DWORD		 dwAllocateTime;
	void*		 addr;
};

using T_STR = std::basic_string<TCHAR>;
using MEM_MAP = std::map<void *, MEMINFO>;
using RECT_VECTOR = std::vector<RECT>;

enum class KEYSTATE
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};
enum class SCENE
{
	LOBBY,
	GAME,
	END
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
	FLOAT x, y;
};

struct Sphere
{
	FLOAT fRadius;
	POINT CenterPos;
};


extern HWND					g_hWnd;
extern HINSTANCE            g_hInstance;
extern HDC					g_hOffScreenDC;
extern HDC					g_hScreenDC;
extern RECT					g_rtClient;
extern float				g_fPerSecFrame;

extern int					g_iNewCount;
extern MEM_MAP				MemoryMap;
