#pragma once
#include "wClass.h"
#include "Timer.h"
#include "Input.h"
class Core : public Window
{
public:
	virtual bool			GameInit() override;
	virtual bool			GameFrame() override;
	virtual bool			GameRender() override;
	virtual bool			GameRelease() override;
	virtual bool			Init() override;
	virtual bool			Frame() override;
	virtual bool			Render() override;
	virtual bool			Release() override;
private:
	bool					GamePreRender();
	bool					GamePostRender();
private:
	HPEN					m_hPen;
	HDC						m_hOffScreenDC;
	HDC						m_hScreenDC;
	HBRUSH					m_bkBrush;
	Timer					m_Timer;
};