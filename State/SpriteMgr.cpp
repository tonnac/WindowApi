#include "SpriteMgr.h"

SpriteMgr::~SpriteMgr()
{
	Release();
}

bool SpriteMgr::Init()
{
	return true;
}
bool SpriteMgr::Frame()
{
	return true;
}
bool SpriteMgr::Render()
{
	return true;
}
bool SpriteMgr::Release()
{
	for (auto it : m_SpriteMap)
	{
		it.second->Release();
		delete it.second;
	}
	m_SpriteMap.clear();
	return true;
}
bool SpriteMgr::SpriteSet(T_STR szSpriteList)
{
	std::ifstream fp(szSpriteList.c_str());
	
	if (!fp.is_open())
	{
		MessageBox(nullptr, L"FILE OPEN", L"FILE OPEN ERROR", MB_OK);
	}
	std::vector<std::string> temp;
	std::string buffer;

	std::getline(fp, buffer);
	int Total = std::stoi(buffer);
	temp.resize(Total);
	for (int i = 0; i < Total; i++)
	{
		int k;
		getline(fp, buffer);
		std::istringstream is(buffer);
		is >> temp[i] >> k;
		//Sprite* pl = New Sprite(k);
		Sprite* pl = New Sprite(k);
		m_SpriteMap.insert(std::make_pair(temp[i], pl));
	}
	while (!fp.eof())
	{
		for (auto it : temp)
		{
			SPRITELIST sl;
			for (int i = 0; i < m_SpriteMap[it]->Size() ;++i)
			{
				int l, t, r, b;
				std::getline(fp, buffer);
				std::istringstream is(buffer);
				is >> l >> t >> r >> b;;
				RECT rt = { l,t,r,b };
				sl.push_back(rt);
			}
			m_SpriteMap[it]->setList(sl);
		}
	}
	return true;
}
Sprite*	SpriteMgr::LoadSprite(T_STR szSpriteName)
{
	std::string fileName(szSpriteName.begin(), szSpriteName.end());
	SPMAP::iterator it;
	it = m_SpriteMap.find(fileName);
	assert(it != m_SpriteMap.end());
	return it->second;
}