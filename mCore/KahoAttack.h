#pragma once
#include "EffectObj.h"


class KahoAttack1 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
private:
};

class KahoAttack2 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
private:
};

class KahoAttack3 : public EffectObj
{
public:
	bool		Init() override;
	bool		Frame() override;
public:
	void * operator new(size_t sz, const char* FileName, int iLine);
	void operator delete(void * p);
private:
};