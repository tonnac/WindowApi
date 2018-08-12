#pragma once
#include "Sprite.h"

class SpriteMgr : public Singleton<SpriteMgr>
{
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
	bool				LoadFile(T_STR);
private:
};