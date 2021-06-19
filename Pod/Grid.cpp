#include "Grid.h"

Grid* Grid::instance;

Grid* Grid::getInstance()
{
	if (instance == NULL) {
		instance = new Grid();
	}
	return instance;
}

vector<vector<vector<Component*>>> Grid::getCells()
{
	return this->cells;
}

vector<Component*> Grid::getCell(int row, int col)
{
	return this->cells[row][col];
}

int Grid::getCellWidth()
{
	return this->cellWidth;
}

int Grid::getCellHeight()
{
	return this->cellHeight;
}

void Grid::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->totalRow = v[0];
	this->totalCol = v[1];
	this->cellHeight = v[2];
	this->cellWidth = v[3];

	this->cells = vector<vector<vector<Component*>>>();

	for (int i = 0; i < this->totalRow; ++i) {
		this->cells.push_back(vector<vector<Component*>>());
		for (int j = 0; j < this->totalCol; ++j) {
			this->cells[i].push_back(vector<Component*>());
		}
	}
}

void Grid::loadMatrixId(vector<string> data, char beginSeperator, char pairSeperator, char seperator)
{
	bool isReadingCell = false;
	int currentID = 0;
	vector<string> pairsStr;
	vector<pair<int, int>> pairs;

	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == beginSeperator) {
			isReadingCell = true;
			currentID = stoi(data[i].substr(2, data[i].length() - 2));
			continue;
		}

		if (isReadingCell == true) {
			// every element in pairs is a pair of cellX, cellY
			pairsStr = Tool::splitToVectorStringFrom(data[i], pairSeperator);
			pairs = vector<pair<int, int>>();
			for (int k = 0; k < pairsStr.size(); ++k) {
				pairs.push_back(Tool::splitToPairIntIntFrom(pairsStr[k], seperator));
			}

			this->matrixId[currentID] = pairs;

			pairsStr.clear();
			pairs.clear();
			isReadingCell = false;
		}
	}
}

void Grid::add(Component* _component)
{
	vector<pair<int, int>> pairs = this->matrixId[_component->getId()];

	for (int i = 0; i < pairs.size(); ++i) {
		int y = pairs[i].second;
		int x = pairs[i].first;

		this->cells[y][x].push_back(_component);
	}
}

