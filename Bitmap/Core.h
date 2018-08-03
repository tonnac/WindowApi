#pragma once
#include "WindowClass.h"
#include "Timer.h"

class Core : public Window
{
public:
	virtual bool			Init() override;
	virtual bool			Frame() override;
	virtual bool			Render() override;
	virtual bool			Release() override;
private:
	Timer					m_Timer;
};