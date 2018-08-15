#pragma once
#include "Object.h"

class State;

class Player : public Object
{
public:
	bool				Init();
	bool				Frame();
private:
	std::array<int, 2>	m_idir;
	State *				m_pState;
};