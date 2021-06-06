#include "SunnyMap.h"

SunnyMap::SunnyMap(LPCWSTR _tileSetPath, D3DCOLOR _transcolor) : Map(_tileSetPath, _transcolor)
{
	Map::Map(_tileSetPath, _transcolor);
}

void SunnyMap::Update(float _dt)
{
}

void SunnyMap::Draw()
{
	Map::Draw();
}

void SunnyMap::loadInfo(string line, char seperator)
{
	Map::loadInfo(line, seperator);
}

void SunnyMap::loadIndexes(vector<string> data, char seperator)
{
	Map::loadIndexes(data, seperator);
}
