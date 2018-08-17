#include "BKObject.h"
#include "InversionRendering.h"
#include "TerrainObject.h"
#include "Collision.h"

//bool BKObject::Init()
//{
//	m_pRendering = New Rendering(this);
//	return true;
//}
bool BKObject::Frame()
{
	for (auto it : m_pObjList)
	{
		it->Frame();
	}
	Object::Frame();
	return true;
}

bool BKObject::Render()
{
	Object::Render();
	if (isDebugMode)
	{
		for (auto it : m_pObjList)
		{
			it->Render();
		}
	}
	return true;
}

bool BKObject::MoveScrollBk(const LONG& fsize)
{
	for (auto it : m_pObjList)
	{
		it->MoveScrollObj(fsize);
	}
	if (fsize < 0)
	{
		m_fScroll += (g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}
	else
	{
		m_fScroll += -(g_fPerSecFrame * g_fSpeed);
		m_rtDraw.left = static_cast<LONG>(m_fScroll);
	}
	return true;
}
void BKObject::AddTerrain(TerrainObject * m_ptObject)
{
	m_pObjList.push_back(m_ptObject);
}
bool BKObject::Collision(Object* pObject)
{
	bool isLanding = false;
	for (auto it : m_pObjList)
	{
		if (it->Collision(pObject))
		{
			isLanding = true;
		}
		RECT ObjRT = *pObject->getCollisionRt();
		RECT rtrt = *it->getCollisionRt();
		RECT faRT = { ObjRT.left + 27, ObjRT.top, ObjRT.right - 27, ObjRT.bottom + 10 };
		if (CollisionClass::RectInRect(faRT, rtrt))
		{
			isLanding = true;
		}
	}
	pObject->setLanding(isLanding);
	return Frame();
}