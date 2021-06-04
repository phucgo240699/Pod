#include "SunnyMap.h"

SunnyMap::SunnyMap(LPCWSTR _tileSetPath, D3DCOLOR _transcolor) : Map(_tileSetPath, _transcolor)
{
	this->rect = RECT();
	this->position = D3DXVECTOR3(0, 0, 0);
}

void SunnyMap::Update(float _dt)
{
}

void SunnyMap::Draw()
{

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

			//position = D3DXVECTOR3(j * tileSize - camera->getX(), i * tileSize - camera->getY(), 0);
			
			position.x = j * tileSize - camera->getX();
			position.y = i * tileSize - camera->getY();

			drawing->draw(texture, &rect, NULL, &position);
		}
	}
}

void SunnyMap::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->setTileSize(v[0]);
	this->setSpaceBetweenTiles(v[1]);
	this->setTilesPerRow(v[2]);
	this->setTilesPerColumn(v[3]);
	this->setWidth(v[4]);
	this->setHeight(v[5]);
}

void SunnyMap::loadIndexes(vector<string> data, char seperator)
{
	this->matrixIds = Tool::getMatrixFrom(data, seperator);
}
