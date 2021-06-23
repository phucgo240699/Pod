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

unordered_set<Component*> Grid::getCell(int row, int col)
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

	this->cells = vector<vector<unordered_set<Component*>>>();

	for (int i = 0; i < this->totalRow; ++i) {
		this->cells.push_back(vector<unordered_set<Component*>>());
		for (int j = 0; j < this->totalCol; ++j) {
			this->cells[i].push_back(unordered_set<Component*>());
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
		int col = pairs[i].first;
		int row = pairs[i].second;

		this->cells[row][col].insert(_component);
	}
}

void Grid::add(Component* _component, int row, int col)
{
	this->cells[row][col].insert(_component);
}

void Grid::updateCellOf(Component* _component)
{
	vector<pair<int, int>> pairs = this->matrixId[_component->getId()];
	RECT r = RECT();

	for (int i = 0; i < pairs.size(); ++i) {
		int col = pairs[i].first;
		int row = pairs[i].second;

		r.top = row * this->cellHeight;
		r.bottom = r.top + this->cellHeight;
		r.left = col * this->cellWidth;
		r.right = r.left + this->cellWidth;

		if (_component->isColliding(r) == false) { // if no longer in this cell, remove it from this cell, and add it to new cell
			this->cells[row][col].erase(_component);
			int newCol = _component->getX() / this->cellWidth;
			int newRow = _component->getY() / this->cellHeight;
			
			if (col != newCol) {
				this->matrixId[_component->getId()][i].first = newCol;
			}
			if (row != newRow) {
				this->matrixId[_component->getId()][i].second = newRow;
			}

			this->add(_component, newRow, newCol);
		}
	}
}
