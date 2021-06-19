#pragma once
#include "Component.h"
#include <unordered_set>
#include <unordered_map>

class Grid
{
private:
	Grid() = default; // 1.Don't public constructor function
	static Grid* instance; // 2. static private instance
	int totalCol = 0, totalRow = 0;
	int cellWidth = 0, cellHeight = 0; // for check which cell collapse to camera

	// first vector layer is rows
	// section vector layer is cols
	vector<vector<vector<Component*>>> cells;

	// id, (cellX1, cellY1, cellX2, cellY2, ...)
	unordered_map<int, vector<pair<int, int>>> matrixId; // indicate which id in which cell;

public:
	Grid(const Grid&) = delete; // 3. delete copy constructor
	static Grid* getInstance();	  // 4. public function for client code usage

	// Getter
	vector<vector<vector<Component*>>> getCells();
	vector<Component*> getCell(int row, int col);
	int getCellWidth();
	int getCellHeight();

	void loadInfo(string line, char seperator);
	void loadMatrixId(vector<string> data, char beginSeperator, char pairSeperator, char seperator);
	void add(Component* _component);
};

