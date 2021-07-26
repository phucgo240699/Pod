#include "Map.h"

//Map::Map(LPCWSTR _tileSetPath, D3DCOLOR _transcolor)
//{
//	this->texture = LoadTextureFromImage(_tileSetPath, _transcolor);
//
//	D3DXIMAGE_INFO info;
//	D3DXGetImageInfoFromFile(_tileSetPath, &info);
//	this->width = info.Width;
//	this->height = info.Height;
//
//	this->rect = RECT();
//	this->position = D3DXVECTOR3(0, 0, 0);
//}

//LPDIRECT3DTEXTURE9 Map::getTexture()
//{
//	return this->texture;
//}

Map::Map()
{
	this->rect = RECT();
	this->position = D3DXVECTOR3(0, 0, 0);
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

void Map::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	// begin ---> end: from left ro right
	Camera* camera = Camera::getInstance();
	Drawing* drawing = Drawing::getInstance();

	int cellIndexBeginX = int(camera->getX() / tileSize);
	int cellIndexEndX = int((camera->getX() + camera->getWidth()) / tileSize);
	//	begin
	//	  |
	//	  |
	//	  v
	//	 end
	// from up to down
	int cellIndexBeginY = int(camera->getY() / tileSize);
	int cellIndexEndY = int((camera->getY() + camera->getHeight()) / tileSize);

	int tileId; // from index 0
	int r, c; // from index 0. These are row, column in tileset
	for (int i = cellIndexBeginY; i <= cellIndexEndY; ++i) {

		if (i < 0 || time_t(i) >= this->matrixIds.size()) {
			continue;
		}

		for (int j = cellIndexBeginX; j <= cellIndexEndX; ++j) {

			if (j < 0 || time_t(j) >= this->matrixIds[0].size()) {
				continue;
			}

			tileId = this->matrixIds[i][j];

			r = tileId / tilesPerRow;
			c = tileId % tilesPerRow;
			rect.top = r * tileSize + r * spaceBetweenTiles;
			rect.bottom = rect.top + tileSize;
			rect.left = c * tileSize + c * spaceBetweenTiles;
			rect.right = rect.left + tileSize;

			//// Postion of a tile compare to position of camera.
			//// (top-left)

			//position = D3DXVECTOR3(j * tileSize - camera->getX(), i * tileSize - camera->getY(), 0);

			position.x = float(round(j * tileSize));
			position.y = float(round(i * tileSize));

			drawing->draw(_texture, rect, NULL, position);
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
