#pragma once
#include "Component.h"
#include <unordered_set>

class Grid
{
private:
	Grid() = default; // 1.Don't public constructor function
	static Grid* instance; // 2. static private instance
	int totalCol = 0, totalRow = 0;
	int cellWidth = 0, cellHeight = 0; // for check which cell collapse to camera
	vector<vector<unordered_set<Component*>>> cells;

public:
	Grid(const Grid&) = delete; // 3. delete copy constructor
	static Grid* getInstance();	  // 4. public function for client code usage

	// Getter
	vector<vector<unordered_set<Component*>>> getCells();
	int getCellWidth();
	int getCellHeight();

	void loadInfo(string line, char seperator);
	void add(Component* _component);
};

