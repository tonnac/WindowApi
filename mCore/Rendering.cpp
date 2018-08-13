#include "Rendering.h"

Rendering::Rendering(Object* ob) : m_DrawPos(ob->getDrawPos()), m_rtDraw(ob->getrtDraw()),
									m_hColorDC(ob->getColorDC()), m_hMaskDC(ob->getMaskDC()),
						m_CenterPos(ob->getCenterPos()), m_rtCollision(ob->getCollisionRt())
{}

bool Rendering::Init()
{
	return true;
}
bool Rendering::Frame()
{
	return true;
}
bool Rendering::Render()
{
	if (m_hMaskDC == nullptr)
	{
		BitBlt(g_hOffScreenDC,
			static_cast<int>(m_DrawPos.x),
			static_cast<int>(m_DrawPos.y),
			m_rtDraw.right,
			m_rtDraw.bottom,
			m_hColorDC,
			m_rtDraw.left,
			m_rtDraw.top,
			SRCCOPY);
		return true;
	}
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hMaskDC,
		m_rtDraw.left,
		m_rtDraw.top, SRCAND);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hColorDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	BitBlt(g_hOffScreenDC,
		static_cast<int>(m_DrawPos.x),
		static_cast<int>(m_DrawPos.y),
		m_rtDraw.right,
		m_rtDraw.bottom,
		m_hMaskDC,
		m_rtDraw.left,
		m_rtDraw.top,
		SRCINVERT);
	return true;
}
bool Rendering::Release()
{
	return true;
}

void * Rendering::operator new(size_t sz, const char* FileName, int iLine)
{
	MEMINFO mem;
	void* pfs = new char[sz];
	mem.addr = pfs;
	mem.filename = FileName;
	mem.line = iLine;
	mem.dwAllocateTime = timeGetTime();
	MemoryMap.insert(std::make_pair(pfs, mem));
	++::g_iNewCount;
	return pfs;
}
void Rendering::operator delete(void * p)
{
	std::map<void*, MEMINFO>::iterator it;
	it = MemoryMap.find(p);
	MemoryMap.erase(it);
	--::g_iNewCount;
	delete p;
}