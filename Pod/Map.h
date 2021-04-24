#pragma once
#include "Tool.h"
#include "Drawing.h"
#include "Camera.h"

using namespace std;

class Map
{
private:
	LPDIRECT3DTEXTURE9 texture;
	vector<vector<int>> matrixIds;
	int tileSize, spaceBetweenTiles, tilesPerRowInTileSet, tilesPerColumnInTileSet;
	float width, height;
public:
	Map(LPCWSTR _tileSetPath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor);
	~Map();

	// Getter
	int getTileSize();
	float getWidth();
	float getHeight();

	void Update(float _dt);
	void Draw();
};