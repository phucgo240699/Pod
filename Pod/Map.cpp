#include "Map.h"

//Map::Map(LPCWSTR _tileSetPath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor)
//{
//	this->texture = LoadTextureFromImage(_tileSetPath, _transcolor);
//
//	D3DXIMAGE_INFO info;
//	D3DXGetImageInfoFromFile(_tileSetPath, &info);
//	this->width = info.Width;
//	this->height = info.Height;
//
//	matrixIds = FileManager::getInstance()->getIntegerMatrixFromTextFile(_matrixIdsPath, _seperatorOfMatrixIds);
//	vector<int> v = Tool::splitToVectorIntegerFrom(FileManager::getInstance()->getStringFromTextFile(_mapInfoPath), ',');
//
//	this->tileSize = v[0];
//	this->spaceBetweenTiles = v[1];
//	this->tilesPerRow = v[2];
//	this->tilesPerColumn = v[3];
//	this->width = v[4];
//	this->height = v[5];
//}

Map::Map(LPCWSTR _tileSetPath, D3DCOLOR _transcolor)
{
	this->texture = LoadTextureFromImage(_tileSetPath, _transcolor);

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_tileSetPath, &info);
	this->width = info.Width;
	this->height = info.Height;
}

Map::~Map()
{
	delete& texture;
	delete& matrixIds;
}

LPDIRECT3DTEXTURE9 Map::getTexture()
{
	return this->texture;
}

int Map::getTileSize()
{
	return this->tileSize;
}

int Map::getSpaceBetweenTiles()
{
	return this->spaceBetweenTiles;
}

int Map::getTilesPerRow()
{
	return this->tilesPerRow;
}

int Map::getTilesPerColumn()
{
	return this->tilesPerColumn;
}

int Map::getWidth()
{
	return this->width;
}

int Map::getHeight()
{
	return this->height;
}

void Map::setTileSize(int _size)
{
	if (_size < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
	this->tileSize = _size;
}

void Map::setSpaceBetweenTiles(int _space)
{
	if (_space < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
	this->spaceBetweenTiles = _space;
}

void Map::setTilesPerRow(int _perRow)
{
	if (_perRow < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
	this->tilesPerRow = _perRow;
}

void Map::setTilesPerColumn(int _perCol)
{
	if (_perCol < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
	this->tilesPerColumn = _perCol;
}

void Map::setWidth(int _width)
{
	if (_width < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
}

void Map::setHeight(int _height)
{
	if (_height < 0) {
		throw "Value must be greater than or equal zero";
		return;
	}
}

void Map::Update(float _dt)
{
}

void Map::Draw()
{
}

void Map::loadInfo(string line, char seperator)
{
}

void Map::loadIndexes(vector<string> data, char seperator)
{
}
