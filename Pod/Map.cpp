#include "Map.h"

Map::Map(LPCWSTR _imagePath, string _matrixIdsPath, string _mapInfoPath, char _seperatorOfMatrixIds, D3DCOLOR _transcolor)
{
	this->tileSetTexture = LoadTextureFromImage(_imagePath, _transcolor);
	matrixIds = FileManager::getInstance()->getIntegerMatrixFromTextFile(_matrixIdsPath, _seperatorOfMatrixIds);
	this->tileSize = stoi(FileManager::getInstance()->getStringFromTextFile(_mapInfoPath));
}

Map::~Map()
{
	delete& tileSetTexture;
	delete& matrixIds;
}

void Map::Update()
{
}

void Map::Draw()
{
	Camera* camera = Camera::getInstance();
	RECT* rect; // for draw a tile in matrix indexes

	// begin ---> end: from left ro right
	int cellIDBeginX = camera->getX() / tileSize;
	int cellIDEndX = (camera->getX() + camera->getWidth()) / tileSize;
	int numberOfTilesPerRow = cellIDEndX - cellIDBeginX;
	//	begin
	//	  |
	//	  |
	//	  v
	//	 end
	// from up to down
	int cellIDBeginY = camera->getY() / tileSize;
	int cellIDEndY = (camera->getY() + camera->getHeight()) / tileSize;
	int numberOfTilesPerColumn = cellIDEndY - cellIDBeginY;

	for (int m = cellIDBeginY; m <= cellIDEndY; ++m) {
		for (int n = cellIDBeginX; n <= cellIDEndX; ++n) {
			rect->top = m * tileSize;
			rect->bottom = rect->top + tileSize;
			rect->left = n * tileSize;
			rect->right = rect->left + tileSize;

			// Postion of a tile compare to position of camera.
			// (top-left)

			D3DXVECTOR3* position = new D3DXVECTOR3(n * tileSize - camera->getX(), m * tileSize - camera->getY(), 0);

			Drawing::getInstance()->draw(tileSetTexture, rect, NULL, position, NULL);
		}
	}
}
