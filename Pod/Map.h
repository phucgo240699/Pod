#pragma once
#include "Tool.h"
#include "Drawing.h"
#include "Camera.h"

using namespace std;

class Map
{
protected:
	LPDIRECT3DTEXTURE9 texture;
	vector<vector<int>> matrixIds;
	int tileSize, spaceBetweenTiles, tilesPerRow, tilesPerColumn;
	int width, height;

	RECT rect; // for draw a tile in matrix indexes
	D3DXVECTOR3 position; // know where to draw a tile in matrix indexes
public:
	//Map(LPCWSTR _tileSetPath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor);
	Map(LPCWSTR _tileSetPath, D3DCOLOR _transcolor);
	~Map();

	// Getter
	LPDIRECT3DTEXTURE9 getTexture();
	int getTileSize();
	int getSpaceBetweenTiles();
	int getTilesPerRow();
	int getTilesPerColumn();
	int getWidth();
	int getHeight();

	// Setter
	void setTileSize(int _size);
	void setSpaceBetweenTiles(int _space);
	void setTilesPerRow(int _perRow);
	void setTilesPerColumn(int _perCol);
	void setWidth(int _width);
	void setHeight(int _height);

	void Update(float _dt);
	void Draw();

	void loadInfo(string line, char seperator);
	void loadIndexes(vector<string> data, char seperator);
};