#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor)
{
	texture = LoadTextureFromImage(_imagePath, _transcolor);
	startTime = GetTickCount();
}

int ScoreBoard::getTime()
{
	return this->time;
}

int ScoreBoard::getWidth()
{
	return this->width;
}

int ScoreBoard::getHeight()
{
	return this->height;
}

int ScoreBoard::getMomentumLevel(int _momentum, int _space)
{
	int result = _momentum / _space;
	if (result < 0) {
		return 0;
	}
	else if (result > 7) {
		return 7;
	}
	else {
		return result;
	}
}

string ScoreBoard::getMomentumKey(int _momentumLevel)
{
	if (_momentumLevel == 1) {
		return "m1";
	}
	else if (_momentumLevel == 2) {
		return "m2";
	}
	else if (_momentumLevel == 3) {
		return "m3";
	}
	else if (_momentumLevel == 4) {
		return "m4";
	}
	else if (_momentumLevel == 5) {
		return "m5";
	}
	else if (_momentumLevel == 6) {
		return "m6";
	}
	else if (_momentumLevel == 7) {
		return "m7";
	}
	else {
		return "m0";
	}
}

int ScoreBoard::getMarioLife()
{
	return marioLife;
}

ScoreBoard* ScoreBoard::instance;

ScoreBoard* ScoreBoard::getInstance()
{
	if (instance == NULL) {
		instance = new ScoreBoard(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));
		instance->load();
	}
	return instance;
}

void ScoreBoard::setTime(int _time)
{
	if (this->time < 0) {
		throw "Time must be greater than or equal to zero";
	}
	this->time = _time;
}

void ScoreBoard::load()
{
	fstream fs;
	fs.open(FilePath::getInstance()->score_board, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<ScoreBoard>") {
			section = SECTION_SCORE_BOARD;
			continue;
		}
		else if (line == "</ScoreBoard>") {
			section = SECTION_NONE;
		}
		else if (line == "<ScoreBoardFrames>") {
			section = SECTION_SCORE_BOARD_FRAMES;
			continue;
		}
		else if (line == "</ScoreBoardFrames>") {
			this->loadFrames(data, '-', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_NONE:
			data.clear();
			break;
		case SECTION_SCORE_BOARD:
			this->loadInfo(line, ',');
			break;
		case SECTION_SCORE_BOARD_FRAMES:
			data.push_back(line);
			break;
		default:
			break;
		}
	}

	fs.close();
}

void ScoreBoard::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);
	this->position = D3DXVECTOR3(stof(v[0]), stof(v[1]), float(0));
	this->momentumX = stoi(v[2]);
	this->momentumY = stoi(v[3]);
	this->marioLifeX = stoi(v[4]);
	this->marioLifeY = stoi(v[5]);
	this->coinX = stoi(v[6]);
	this->coinY = stoi(v[7]);
	this->pointX = stoi(v[8]);
	this->pointY = stoi(v[9]);
	this->timeX = stoi(v[10]);
	this->timeY = stoi(v[11]);
	this->momentum = stoi(v[12]);
	this->marioLife = stoi(v[13]);
	this->coin = stoi(v[14]);
	this->point = stoi(v[15]);
	this->time = stoi(v[16]);
	this->width = stoi(v[17]);
	this->height = stoi(v[18]);
	this->firstItemX = stoi(v[19]);
	this->firstItemY = stoi(v[20]);
	this->secondItemX = stoi(v[21]);
	this->secondItemY = stoi(v[22]);
	this->thirdItemX = stoi(v[23]);
	this->thirdItemY = stoi(v[24]);
}

void ScoreBoard::Update(float _dt)
{
	if (time > 0) {
		if (GetTickCount() - startTime >= 1000) {
			startTime = GetTickCount();
			time -= 1;
		}
	}
}

void ScoreBoard::Draw()
{
 	Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame("MB"), this->position);
	this->DrawMomentum();
	this->DrawMarioLife();
	this->DrawCoin();
	this->DrawPoint();
	this->DrawTime();
	this->DrawItems();
}

void ScoreBoard::DrawMarioLife()
{
	string str = Tool::getStringNumberFrom(marioLife, 1);
	drawingPosition.y = this->position.y + marioLifeY;

	for (size_t i = 0; i < str.size(); ++i) {
		drawingPosition.x = this->position.x + marioLifeX + i * 8;
		Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame(str.substr(i, 1)), drawingPosition);
	}
}

void ScoreBoard::DrawCoin()
{
	string str = Tool::getStringNumberFrom(coin, 2);
	drawingPosition.y = this->position.y + coinY;

	for (size_t i = 0; i < str.size(); ++i) {
		drawingPosition.x = this->position.x + coinX + i * 8;
		Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame(str.substr(i, 1)), drawingPosition);
	}
}

void ScoreBoard::DrawPoint()
{
	string str = Tool::getStringNumberFrom(point, 7);
	drawingPosition.y = this->position.y + pointY;

	for (size_t i = 0; i < str.size(); ++i) {
		drawingPosition.x = this->position.x + pointX + i * 8;
		Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame(str.substr(i, 1)), drawingPosition);
	}
}

void ScoreBoard::DrawTime()
{
	string str = Tool::getStringNumberFrom(time, 3);
	drawingPosition.y = this->position.y + timeY;

	for (size_t i = 0; i < str.size(); ++i) {
		drawingPosition.x = this->position.x + timeX + i * 8;
		Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame(str.substr(i, 1)), drawingPosition);
	}
}

void ScoreBoard::DrawMomentum()
{
	drawingPosition.x = this->position.x + momentumX;
	drawingPosition.y = this->position.y + momentumY;
	Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame(this->getMomentumKey(this->momentumLevel)), drawingPosition);
}

void ScoreBoard::DrawItems()
{
	for (size_t i = 0; i < this->items.size(); ++i) {
		if (i == size_t(0)) {
			drawingPosition.x = this->position.x + firstItemX;
			drawingPosition.y = this->position.y + firstItemY;
			Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame("i1"), drawingPosition);
		}
		else if (i == size_t(1)) {
			drawingPosition.x = this->position.x + secondItemX;
			drawingPosition.y = this->position.y + secondItemY;
			Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame("i2"), drawingPosition);
		}
		else if (i == size_t(2)) {
			drawingPosition.x = this->position.x + thirdItemX;
			drawingPosition.y = this->position.y + thirdItemY;
			Drawing::getInstance()->drawWithoutCamera(this->texture, this->getFrame("i3"), drawingPosition);
		}
	}
}

RECT ScoreBoard::getFrame(string keyword)
{
	return this->frames[keyword];
}

void ScoreBoard::loadFrames(vector<string> data, char keywordSeperator, char seperator)
{
	for (size_t i = 0; i < data.size(); ++i) {
		vector<string> portion = Tool::splitToVectorStringFrom(data[i], keywordSeperator);
		frames[portion[0]] = Tool::getRECT(portion[1], seperator);
	}
}

void ScoreBoard::plusPoint(int _value)
{
	if (_value < 0) {
		throw "Value must be greater than or equal than zero";
	}
	this->point += _value;
}

void ScoreBoard::plusCoin(int _value)
{
	if (_value < 0) {
		throw "Value must be greater than or equal than zero";
	}
	this->coin += _value;
}

void ScoreBoard::minusMarioLife()
{
	--this->marioLife;
}

void ScoreBoard::resetTimeToZero()
{
	this->time = 0;
}

void ScoreBoard::resetTimeTo300()
{
	this->time = 300;
}

void ScoreBoard::setMomentum(int _momentum)
{
	this->momentum = _momentum;
}

void ScoreBoard::setMomentumLevel(int _momentumLevel)
{
	this->momentumLevel = _momentumLevel;
}

void ScoreBoard::plusMarioLife(int _value)
{
	this->marioLife += _value;
}

void ScoreBoard::addItem(ScoreBoardItemType _item)
{
	if (this->items.size() < size_t(3)) {
		this->items.push_back(_item);
	}
}
