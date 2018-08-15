#include "BKObject.h"
#include "InversionRendering.h"

bool BKObject::Init()
{
	m_pRendering = New Rendering(this);
	return true;
}
//bool BKObject::Frame()
//{
//	return true;
//}
//
//bool BKObject::Render()
//{
//	return true;
//}