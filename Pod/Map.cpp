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
	this->tilesPerRowInTileSet = v[2];
	this->tilesPerColumnInTileSet = v[3];
	this->width = v[4];
	this->height = v[5];
}

Map::~Map()
{
	delete& texture;
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

void Map::Update(int _dt)
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
		for (int j = cellIndexBeginX; j <= cellIndexEndX; ++j) {
			
			if (j == matrixIds[rowIndex].size()) {
				columnIndex = j - 1;
			}
			else {
				columnIndex = j;
			}

			tileId = this->matrixIds[rowIndex][columnIndex];

			r = tileId / tilesPerRowInTileSet;
			c = tileId % tilesPerRowInTileSet;
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
