#pragma once
#include "Map.h"

class WorldMap : public Map
{
public:
	WorldMap(LPCWSTR _tileSetPath, D3DCOLOR _transcolor);

	void Update(float _dt);
	void Draw();

	void loadInfo(string line, char seperator);
	void loadIndexes(vector<string> data, char seperator);
};