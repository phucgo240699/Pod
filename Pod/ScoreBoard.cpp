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

ScoreBoard* ScoreBoard::instance;

ScoreBoard* ScoreBoard::getInstance()
{
	if (instance == NULL) {
		instance = new ScoreBoard(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));
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

void ScoreBoard::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->position = new D3DXVECTOR3(v[0], v[1], 0);
	this->coinX = v[2];
	this->coinY = v[3];
	this->pointX = v[4];
	this->pointY = v[5];
	this->timeX = v[6];
	this->timeY = v[7];
	this->coin = v[8];
	this->point = v[9];
	this->time = v[10];
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
 	Drawing::getInstance()->draw(this->texture, this->getFrame("MB"), this->position);
	this->DrawCoin();
	this->DrawPoint();
	this->DrawTime();
}

RECT ScoreBoard::getFrame(string keyword)
{
	return this->frames[keyword];
}

void ScoreBoard::loadFrames(vector<string> data, char keywordSeperator, char seperator)
{
	for (int i = 0; i < data.size(); ++i) {
		vector<string> portion = Tool::splitToVectorStringFrom(data[i], keywordSeperator);
		frames[portion[0]] = Tool::getRECT(portion[1], seperator);
	}
}

void ScoreBoard::DrawCoin()
{
	string str = Tool::getStringNumberFrom(coin, 2);

	for (int i = 0; i < str.size(); ++i) {
		Drawing::getInstance()->draw(this->texture, this->getFrame(str.substr(i, 1)), new D3DXVECTOR3(this->position->x + coinX + i * 8, this->position->y + coinY, 0));
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

void ScoreBoard::DrawPoint()
{
	string str = Tool::getStringNumberFrom(point, 7);

	for (int i = 0; i < str.size(); ++i) {
		Drawing::getInstance()->draw(this->texture, this->getFrame(str.substr(i, 1)), new D3DXVECTOR3(this->position->x + pointX + i * 8, this->position->y + pointY, 0));
	}
}

void ScoreBoard::DrawTime()
{
	string str = Tool::getStringNumberFrom(time, 3);

	for (int i = 0; i < str.size(); ++i) {
		Drawing::getInstance()->draw(this->texture, this->getFrame(str.substr(i, 1)), new D3DXVECTOR3(this->position->x + timeX + i * 8, this->position->y + timeY, 0));
	}
}
