#pragma once
#include "Drawing.h"
#include "Camera.h"

class Map
{
private:
	LPDIRECT3DTEXTURE9 tileSetTexture;
	vector<vector<int>> matrixIds;
	int tileSize;
public:
	Map(LPCWSTR _imagePath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor);
	~Map();

	void Update();
	void Draw();
};