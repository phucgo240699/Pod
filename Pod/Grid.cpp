#include "Grid.h"

Grid* Grid::instance;

Grid* Grid::getInstance()
{
	if (instance == NULL) {
		instance = new Grid();
	}
	return instance;
}

vector<vector<unordered_set<Component*>>> Grid::getCells()
{
	return this->cells;
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

	this->cells = vector<vector<unordered_set<Component*>>>();

	for (int i = 0; i < this->totalRow; ++i) {
		this->cells.push_back(vector<unordered_set<Component*>>());
		for (int j = 0; j < this->totalCol; ++j) {
			this->cells[i].push_back(unordered_set<Component*>());
		}
	}
}

void Grid::add(Component* _component)
{
	this->cells.at(_component->getCellY()).at(_component->getCellX()).insert(_component);
}

