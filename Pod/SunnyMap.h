#pragma once
#include "Map.h"

class SunnyMap : public Map
{
private:
	RECT rect; // for draw a tile in matrix indexes
	D3DXVECTOR3 position; // know where to draw a tile in matrix indexes

public:
	SunnyMap(LPCWSTR _tileSetPath, D3DCOLOR _transcolor);

	void Update(float _dt);
	void Draw();

	void loadInfo(string line, char seperator);
	void loadIndexes(vector<string> data, char seperator);
};

