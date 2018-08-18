#pragma once
#include "Std.h"

class Collision
{
public:
	static bool					RectInPt(RECT, POINT);
	static bool					RectInRect(RECT, RECT);
	static bool					SphereInPt(RECT, POINT);
	static bool					SphereInSphere(RECT, RECT);
private:
};