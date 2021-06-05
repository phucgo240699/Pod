#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor)
{
	texture = LoadTextureFromImage(_imagePath, _transcolor);
}

void ScoreBoard::loadPosition(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);
	this->position = new D3DXVECTOR3(v[0], v[1], 0);
}

void ScoreBoard::Update(float _dt)
{
}

void ScoreBoard::Draw()
{
	Drawing::getInstance()->draw(this->texture, NULL, NULL, this->position);
}
