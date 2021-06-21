#include "WorldMap.h"

WorldMap::WorldMap(LPCWSTR _tileSetPath, D3DCOLOR _transcolor) : Map(_tileSetPath, _transcolor)
{
}

void WorldMap::Update(float _dt)
{
}

void WorldMap::Draw()
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
	for (int i = cellIndexBeginY; i < cellIndexEndY; ++i) {

		if (i < 0 || i >= this->matrixIds.size()) {
			continue;
		}

		for (int j = cellIndexBeginX; j < cellIndexEndX; ++j) {

			if (j < 0 || j >= this->matrixIds[0].size()) {
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

			position.x = round(j * tileSize - camera->getX());
			position.y = round(i * tileSize - camera->getY());

			drawing->draw(texture, rect, NULL, position);
		}
	}
}

void WorldMap::loadInfo(string line, char seperator)
{
	Map::loadInfo(line, seperator);
}

void WorldMap::loadIndexes(vector<string> data, char seperator)
{
	Map::loadIndexes(data, seperator);
}
