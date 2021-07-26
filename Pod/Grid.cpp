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

int Grid::getTotalRows()
{
	return this->totalRow;
}

int Grid::getTotalCols()
{
	return this->totalCol;
}

void Grid::loadOriginalSunnyMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->original_grid_sunny_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
			case SECTION_GRID_INFO:
			{
				this->loadInfo(line, ',');
				break;
			}
			case SECTION_GRID_MATRIX_ID:
			{
				data.push_back(line);
				break;
			}
		}
	}
	fs.close();
}

void Grid::loadOriginalUnderGroundMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->original_grid_underground_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_GRID_INFO:
		{
			this->loadInfo(line, ',');
			break;
		}
		case SECTION_GRID_MATRIX_ID:
		{
			data.push_back(line);
			break;
		}
		}
	}
	fs.close();
}

void Grid::loadOriginalThirdMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->original_grid_third_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_GRID_INFO:
		{
			this->loadInfo(line, ',');
			break;
		}
		case SECTION_GRID_MATRIX_ID:
		{
			data.push_back(line);
			break;
		}
		}
	}
	fs.close();
}

void Grid::loadOriginalCloudyMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->original_grid_cloudy_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_GRID_INFO:
		{
			this->loadInfo(line, ',');
			break;
		}
		case SECTION_GRID_MATRIX_ID:
		{
			data.push_back(line);
			break;
		}
		}
	}
	fs.close();
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

	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i][0] == beginSeperator) {
			isReadingCell = true;
			currentID = stoi(data[i].substr(2, data[i].length() - 2));
			continue;
		}

		if (isReadingCell == true) {
			// every element in pairs is a pair of cellX, cellY
			pairsStr = Tool::splitToVectorStringFrom(data[i], pairSeperator);
			pairs = vector<pair<int, int>>();
			for (size_t k = 0; k < pairsStr.size(); ++k) {
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
	//if (_component->getId() == 951) {
	//	int asd = 0;
	//}
	vector<pair<int, int>> pairs = this->matrixId[_component->getId()];

	for (size_t i = 0; i < pairs.size(); ++i) {
		int col = pairs[i].first;
		int row = pairs[i].second;

		this->cells[row][col].insert(_component);
	}
}

void Grid::add(Component* _component, int row, int col)
{
	this->cells[row][col].insert(_component);
}

void Grid::remove(Component* _component, int row, int col)
{
	this->cells[row][col].erase(_component);
}

void Grid::updateCellOf(Component* _component)
{
	vector<pair<int, int>> pairs = this->matrixId[_component->getId()];
	RECT r = RECT();

	for (size_t i = 0; i < pairs.size(); ++i) {
		int col = pairs[i].first;
		int row = pairs[i].second;

		r.top = row * this->cellHeight;
		r.bottom = r.top + this->cellHeight;
		r.left = col * this->cellWidth;
		r.right = r.left + this->cellWidth;

		if (_component->isCollidingByFrame(r) == false) { // if no longer in this cell, remove it from this cell, and add it to new cell
			this->cells[row][col].erase(_component);
			int newCol = int(_component->getX() / this->cellWidth);
			int newRow = int(_component->getY() / this->cellHeight);
			
			if (col != newCol && newCol < this->getTotalCols()) {
				this->matrixId[_component->getId()][i].first = newCol;
			}
			if (row != newRow && newRow < this->getTotalRows()) {
				this->matrixId[_component->getId()][i].second = newRow;
			}
			if (newCol < this->getTotalCols() && newRow < this->getTotalRows()) {
				this->add(_component, newRow, newCol);
			}
		}
	}
}

void Grid::saveCurrentSunnyMap()
{
	vector<string> data = vector<string>();
	string line = "";
	data.push_back("<GridInfo>");
	data.push_back("\n");
	data.push_back(to_string(this->totalRow) + "," + to_string(this->totalCol) + "," + to_string(this->cellHeight) + "," + to_string(this->cellWidth));
	data.push_back("\n");
	data.push_back("</GridInfo>");
	data.push_back("\n");
	data.push_back("\n");

	data.push_back("<GridMatrixId>");
	data.push_back("\n");
	for (auto itr = this->matrixId.begin(); itr != this->matrixId.end(); itr++) {
		data.push_back("> " + to_string((*itr).first));
		data.push_back("\n");
		
		line = "";
		for (size_t i = 0; i < (*itr).second.size(); ++i) {
			line += to_string((*itr).second[i].first); // col
			line += ",";
			line += to_string((*itr).second[i].second); // row

			if (i != (*itr).second.size() - 1) {
				line += "_";
			}
		}
		data.push_back(line);
		data.push_back("\n");
		data.push_back("\n");
	}
	data.push_back("</GridMatrixId>");


	fstream fs;
	fs.open(FilePath::getInstance()->current_grid_sunny_map, ios::out);

	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i] == "\n") {
			fs << endl;
		}
		else {
			fs << data[i];
		}
	}

	fs.close();
}

void Grid::saveCurrentThirdMap()
{
	vector<string> data = vector<string>();
	string line = "";
	data.push_back("<GridInfo>");
	data.push_back("\n");
	data.push_back(to_string(this->totalRow) + "," + to_string(this->totalCol) + "," + to_string(this->cellHeight) + "," + to_string(this->cellWidth));
	data.push_back("\n");
	data.push_back("</GridInfo>");
	data.push_back("\n");
	data.push_back("\n");

	data.push_back("<GridMatrixId>");
	data.push_back("\n");
	for (auto itr = this->matrixId.begin(); itr != this->matrixId.end(); itr++) {
		data.push_back("> " + to_string((*itr).first));
		data.push_back("\n");

		line = "";
		for (size_t i = 0; i < (*itr).second.size(); ++i) {
			line += to_string((*itr).second[i].first); // col
			line += ",";
			line += to_string((*itr).second[i].second); // row

			if (i != (*itr).second.size() - 1) {
				line += "_";
			}
		}
		data.push_back(line);
		data.push_back("\n");
		data.push_back("\n");
	}
	data.push_back("</GridMatrixId>");


	fstream fs;
	fs.open(FilePath::getInstance()->current_grid_third_map, ios::out);

	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i] == "\n") {
			fs << endl;
		}
		else {
			fs << data[i];
		}
	}

	fs.close();
}

void Grid::loadCurrentSunnyMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->current_grid_sunny_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_GRID_INFO:
		{
			this->loadInfo(line, ',');
			break;
		}
		case SECTION_GRID_MATRIX_ID:
		{
			data.push_back(line);
			break;
		}
		}
	}
	fs.close();
}

void Grid::loadCurrentThirdMap()
{
	fstream fs;
	fs.open(FilePath::getInstance()->current_grid_third_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	if (this->cells.size() > 0) {
		this->cells.clear();
	}
	if (this->matrixId.size() > 0) {
		this->matrixId.clear();
	}

	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			this->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_GRID_INFO:
		{
			this->loadInfo(line, ',');
			break;
		}
		case SECTION_GRID_MATRIX_ID:
		{
			data.push_back(line);
			break;
		}
		}
	}
	fs.close();
}

bool Grid::checkExist(Component* _component, int beginRow, int endRow, int beginCol, int endCol)
{
	if (_component->getFrame().bottom < beginRow * this->cellWidth) return false;
	else if (_component->getY() > (endRow + 1) * this->cellWidth) return false;
	else if (_component->getFrame().right < beginCol * this->cellHeight) return false;
	else if (_component->getX() > (endCol + 1) * this->cellHeight) return false;

	return true;
}
