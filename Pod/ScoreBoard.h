#pragma once
#include "Drawing.h"
#include <unordered_map>

using namespace std;

class ScoreBoard
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3* position;
	unordered_map<string, RECT> frames;

	long startTime;
	int time = 300;
	int pointX, pointY, timeX, timeY, moneyX, moneyY;
public:
	// Init
	ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor);

	RECT getFrame(string keyword);

	void loadPosition(string line, char seperator);
	void loadFrames(vector<string> data, char keywordSeperator, char seperator);

	void Update(float _dt);
	void Draw();
	void DrawTime();
};

