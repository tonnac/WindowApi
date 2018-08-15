#include "Sprite.h"

Sprite::Sprite(const int& k)
{
	m_spritelist.resize(k);

	m_fSpriteTime = 0.0f;
	m_fDivideTime = 1.0f;
	m_iIndex = 0;

	m_fOffset = m_fDivideTime / m_spritelist.size();
}
Sprite::~Sprite()
{

}

bool Sprite::Init()
{
	return true;
}
bool Sprite::Frame()
{
	return true;
}
bool Sprite::Render()
{
	return true;
}
bool Sprite::Release()
{
	return true;
}
bool Sprite::setList(const SPRITELIST& rt)
{
	m_spritelist = rt;
	return true;
}
size_t Sprite::Size()
{
	return m_spritelist.size();
}
bool Sprite::setDivideTime(const FLOAT& offset)
{
	m_fDivideTime = offset;
	return true;
}
RECT Sprite::getSpriteRt(const INT& index)
{
	m_fSpriteTime += g_fPerSecFrame;
	if (m_fSpriteTime >= m_fOffset)
	{
		m_fSpriteTime -= m_fOffset;
		if (++m_iIndex >= m_spritelist.size())
		{
			m_iIndex = index;
		}
	}
	return m_spritelist[m_iIndex];
}
void * Sprite::operator new(size_t sz, const char* FileName, int iLine)
{
	MEMINFO mem;
	void* pfs = malloc(sz);
	mem.addr = pfs;
	mem.filename = FileName;
	mem.line = iLine;
	mem.dwAllocateTime = timeGetTime();
	MemoryMap.insert(std::make_pair(pfs, mem));
	++::g_iNewCount;
	return pfs;
}
void Sprite::operator delete(void * p)
{
	std::map<void*, MEMINFO>::iterator it;
	it = MemoryMap.find(p);
	MemoryMap.erase(it);
	--::g_iNewCount;
	free(p);
}