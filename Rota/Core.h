#pragma once
#include "Win.h"

class Core : public Window
{
public:
	virtual bool		GameInit() override;
	virtual bool		GameFrame() override;
	virtual bool		GameRender() override;
	virtual bool		GameRelease() override;
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
	Core(HINSTANCE a, LONG b, LONG c);
protected:
	HDC						m_hScreenDC;
	HDC						m_hOffScreenDC;
private:

};