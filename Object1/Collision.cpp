#include "Collision.h"

bool Collision::RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT cCenterDesk, cCenterSrc;
	cCenterDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cCenterDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cCenterSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cCenterSrc.y = (rtSrc.top + rtSrc.bottom) / 2;

	POINT deskRadius, srcRadius;
	deskRadius.x = (rtDesk.right - rtDesk.left) * 0.5f;
	deskRadius.y = (rtDesk.bottom - rtDesk.top) * 0.5f;
	srcRadius.x = (rtSrc.right - rtSrc.left) * 0.5f;
	srcRadius.y = (rtSrc.bottom - rtSrc.top) * 0.5f;

	if (abs(cCenterDesk.x - cCenterSrc.x) < (deskRadius.x + srcRadius.x) &&
		abs(cCenterDesk.y - cCenterSrc.y) < (deskRadius.y + srcRadius.y))
	{
		return true;
	}
	return false;
}
bool Collision::RectInPoint(RECT rtDesk, POINT pt)
{
	if ((pt.x <= rtDesk.right) && (pt.x >= rtDesk.left))
	{
		if ((pt.y <= rtDesk.bottom) && (pt.y >= rtDesk.top))
		{
			return true;
		}
	}
	return false;
}
bool Collision::SphereInSphere(RECT rtDesk, RECT rtSrc)
{
	Sphere deskSphere, srcSphere;
	deskSphere.CenterPos.x = (rtDesk.right + rtDesk.left) / 2;
	deskSphere.CenterPos.y = (rtDesk.bottom + rtDesk.top) / 2;
	srcSphere.CenterPos.x = (rtSrc.right + rtSrc.left) / 2;
	srcSphere.CenterPos.y = (rtSrc.bottom + rtSrc.top) / 2;

	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	deskSphere.m_fRadius = (dwX < dwY) ? dwY : dwX;
	dwX = rtSrc.right - rtSrc.left;
	dwY = rtSrc.bottom - rtSrc.top;
	srcSphere.m_fRadius = (dwX < dwY) ? dwY : dwX;

	float centerDiff = sqrt((deskSphere.CenterPos.x - srcSphere.CenterPos.x) * (deskSphere.CenterPos.x - srcSphere.CenterPos.x)
		+ (deskSphere.CenterPos.y - srcSphere.CenterPos.y) * (deskSphere.CenterPos.y - srcSphere.CenterPos.y));

	if (centerDiff < deskSphere.m_fRadius + srcSphere.m_fRadius)
	{
		return true;
	}

	return false;
}
bool Collision::SphereInPoint(RECT rtDesk, POINT pt)
{
	Sphere deskSphere;
	deskSphere.CenterPos.x = (rtDesk.right + rtDesk.left) / 2;
	deskSphere.CenterPos.y = (rtDesk.bottom + rtDesk.top) / 2;

	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	deskSphere.m_fRadius = (dwX < dwY) ? dwY : dwX;

	float pointDiff = sqrt((deskSphere.CenterPos.x - pt.x) * (deskSphere.CenterPos.x - pt.x)
		+ (deskSphere.CenterPos.y - pt.y) * (deskSphere.CenterPos.y - pt.y));

	if (pointDiff < deskSphere.m_fRadius)
	{
		return true;
	}

	return false;
}