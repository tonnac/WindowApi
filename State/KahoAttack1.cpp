#include "KahoAttack1.h"

bool KahoAttack1::Init()
{
	Sprite * pe = S_SpriteMgr.LoadSprite(L"Kaho", L"Leaf1");
	pe->setIndex(0);
	setSprite(pe);
	Object::Init();
	return true;
}
//bool KahoAttack1::Frame()
//{
//	
//	return true;
//}