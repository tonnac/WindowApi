#pragma once
#include "Object.h"

class State;

using StateMap = std::map<std::string, State*>;

class Player : public Object
{
public:
	Player();
public:
	bool			Init		();
	bool			Frame		();
public:
	void			setState	(T_STR);
public:
	INT				getDir		();
	void			setDir		(const INT&);
public:
	void			addState(std::string, State*);
private:
	INT				m_iCurrentDir;
	StateMap		m_pStateList;
	State *			m_pCurrentState;
};