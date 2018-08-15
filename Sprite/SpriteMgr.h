#pragma once
#include "Sprite.h"
#include <fstream>
#include <sstream>

using SPMAP = std::map<std::string, Sprite*>;

class SpriteMgr : public Singleton<SpriteMgr>
{
	friend class Singleton<SpriteMgr>;
public:
	~SpriteMgr();
public:
	bool				Init();
	bool				Frame();
	bool				Render();
	bool				Release();
public:
	bool				SpriteSet(T_STR);
	Sprite*				LoadSprite(T_STR);
private:
	SPMAP				m_SpriteMap;
};


#define S_SpriteMgr SpriteMgr::getInstance()