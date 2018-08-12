#pragma once
#include "Sprite.h"

class Player
{
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
private:
	Sprite pe;
};