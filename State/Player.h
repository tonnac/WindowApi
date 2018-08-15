#pragma once
#include "Object.h"

class State;

class Player : public Object
{
public:
	Player();
public:
	bool				Init		();
	bool				Frame		();
public:
	void				setIdle		();
	void				setBrake	();
	void				setRun		();
public:
	INT					getDir		();
	void				setDir		(const INT&);
private:
	INT					m_iCurrentDir;
	std::vector<State*>	m_pStateList;
	State *				m_pCurrentState;
};