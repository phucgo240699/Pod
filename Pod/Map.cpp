#include "Map.h"

Map::Map(LPCWSTR _tileSetPath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor)
{
	this->tileSetTexture = LoadTextureFromImage(_tileSetPath, _transcolor);

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_tileSetPath, &info);
	this->width = info.Width;
	this->height = info.Height;

	matrixIds = FileManager::getInstance()->getIntegerMatrixFromTextFile(_matrixIdsPath, _seperatorOfMatrixIds);
	vector<int> v = Tool::splitToVectorIntegerFrom(FileManager::getInstance()->getStringFromTextFile(_mapInfoPath), ',');

	this->tileSize = v[0];
	this->width = v[1];
	this->height = v[2];
}

Map::~Map()
{
	delete& tileSetTexture;
	delete& matrixIds;
}

int Map::getTileSize()
{
	return this->tileSize;
}

float Map::getWidth()
{
	return this->width;
}

float Map::getHeight()
{
	return this->height;
}

void Map::Update()
{
}

void Map::Draw()
{
	RECT rect; // for draw a tile in matrix indexes
	D3DXVECTOR3 position; // know where to draw a tile in matrix indexes

	// begin ---> end: from left ro right
	Camera* a = Camera::getInstance();
	int cellIndexBeginX = Camera::getInstance()->getX() / tileSize;
	int cellIndexEndX = (Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / tileSize;
	int numberOfTilesPerRow = cellIndexEndX - cellIndexBeginX;
	//	begin
	//	  |
	//	  |
	//	  v
	//	 end
	// from up to down
	int cellIndexBeginY = Camera::getInstance()->getY() / tileSize;
	int cellIndexEndY = (Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / tileSize;
	//int numberOfTilesPerColumn = cellIndexEndY - cellIndexBeginY;
	int tileId;
	for (int j = cellIndexBeginY; j <= cellIndexEndY; ++j) {
		int rowIndex = j;
		if (j == cellIndexEndY) {
			rowIndex = j - 1;
		}
		for (int i = cellIndexBeginX; i <= cellIndexEndX; ++i) {
			int columnIndex = i;
			if (i == cellIndexEndX) {
				columnIndex = i - 1;
			}
			tileId = this->matrixIds[rowIndex][columnIndex];


			rect.top = (tileId / numberOfTilesPerRow) * tileSize;
			rect.bottom = rect.top + tileSize;
			rect.left = (tileId % numberOfTilesPerRow) * tileSize;
			rect.right = rect.left + tileSize;

			//// Postion of a tile compare to position of camera.
			//// (top-left)

			position = D3DXVECTOR3(i * tileSize - Camera::getInstance()->getX(), j * tileSize - Camera::getInstance()->getY(), 0);
			

			Drawing::getInstance()->draw(tileSetTexture, &rect, NULL, &position);
		}
	}
}
