#pragma once
#include "WindowClass.h"

struct Sphere
{
	POINT CenterPos;
	float m_fRadius;
};

class Collision
{
public:
	static bool			RectInRect(RECT, RECT);
	static bool			RectInPoint(RECT, POINT);
	static bool			SphereInSphere(RECT, RECT);
	static bool			SphereInPoint(RECT, POINT);
private:
};