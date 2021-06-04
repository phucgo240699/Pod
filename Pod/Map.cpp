#include "Map.h"

Map::Map(LPCWSTR _tileSetPath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor)
{
	this->texture = LoadTextureFromImage(_tileSetPath, _transcolor);

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_tileSetPath, &info);
	this->width = info.Width;
	this->height = info.Height;

	matrixIds = FileManager::getInstance()->getIntegerMatrixFromTextFile(_matrixIdsPath, _seperatorOfMatrixIds);
	vector<int> v = Tool::splitToVectorIntegerFrom(FileManager::getInstance()->getStringFromTextFile(_mapInfoPath), ',');

	this->tileSize = v[0];
	this->spaceBetweenTiles = v[1];
	this->tilesPerRow = v[2];
	this->tilesPerColumn = v[3];
	this->width = v[4];
	this->height = v[5];
}

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
	RECT rect; // for draw a tile in matrix indexes
	D3DXVECTOR3 position; // know where to draw a tile in matrix indexes

	// begin ---> end: from left ro right
	Camera* camera = Camera::getInstance();
	Drawing* drawing = Drawing::getInstance();
	
	int cellIndexBeginX = camera->getX() / tileSize;
	int cellIndexEndX = (camera->getX() + camera->getWidth()) / tileSize;
	//	begin
	//	  |
	//	  |
	//	  v
	//	 end
	// from up to down
	int cellIndexBeginY = camera->getY() / tileSize;
	int cellIndexEndY = (camera->getY() + camera->getHeight()) / tileSize;

	int tileId; // from index 0
	int r, c; // from index 0. These are row, column in tileset
	int rowIndex, columnIndex; // from index 0. These are row, column in matrix indexes
	for (int i = cellIndexBeginY; i <= cellIndexEndY; ++i) {
		
		if (i == matrixIds.size()) {
			rowIndex = i - 1;
		}
		else {
			rowIndex = i;
		}
		if (rowIndex < 0 || rowIndex >= this->matrixIds.size()) {
			continue;
		}
		for (int j = cellIndexBeginX; j <= cellIndexEndX; ++j) {
			
			if (j == matrixIds[rowIndex].size()) {
				columnIndex = j - 1;
			}
			else {
				columnIndex = j;
			}

			if (columnIndex < 0 || columnIndex >= this->matrixIds[0].size()) {
				continue;
			}

			tileId = this->matrixIds[rowIndex][columnIndex];

			r = tileId / tilesPerRow;
			c = tileId % tilesPerRow;
			rect.top = r * tileSize + r * spaceBetweenTiles;
			rect.bottom = rect.top + tileSize;
			rect.left = c * tileSize + c * spaceBetweenTiles;
			rect.right = rect.left + tileSize;

			//// Postion of a tile compare to position of camera.
			//// (top-left)
			
			position = D3DXVECTOR3(j * tileSize - camera->getX(), i * tileSize - camera->getY(), 0);
			

			drawing->draw(texture, &rect, NULL, &position);
		}
	}
}

void Map::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->setTileSize(v[0]);
	this->setSpaceBetweenTiles(v[1]);
	this->setTilesPerRow(v[2]);
	this->setTilesPerColumn(v[3]);
	this->setWidth(v[4]);
	this->setHeight(v[5]);
}

void Map::loadIndexes(vector<string> data, char seperator)
{
	this->matrixIds = Tool::getMatrixFrom(data, seperator);
}
