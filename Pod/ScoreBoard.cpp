#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor)
{
	texture = LoadTextureFromImage(_imagePath, _transcolor);
	startTime = GetTickCount();
}

void ScoreBoard::loadPosition(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->position = new D3DXVECTOR3(v[0], v[1], 0);
	this->moneyX = v[2];
	this->moneyY = v[3];
	this->pointX = v[4];
	this->pointY = v[5];
	this->timeX = v[6];
	this->timeY = v[7];
}

void ScoreBoard::Update(float _dt)
{
	if (GetTickCount() - startTime >= 1000) {
		startTime = GetTickCount();
		time -= 1;
	}
}

void ScoreBoard::Draw()
{
 	Drawing::getInstance()->draw(this->texture, this->getFrame("MB"), this->position);
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

void ScoreBoard::DrawTime()
{
	string str = std::to_string(time);
	if (str.size() == 1) {
		str = ("00" + str);
	}
	if (str.size() == 2) {
		str = ("0" + str);
	}
	for (int i = 0; i < str.size() ; ++i) {
		Drawing::getInstance()->draw(this->texture, this->getFrame(str.substr(i, 1)), new D3DXVECTOR3(this->position->x + timeX + i * 8, this->position->y + timeY, 0));
	}
}
