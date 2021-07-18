#pragma once
#include "Drawing.h"
#include <unordered_map>

using namespace std;

class ScoreBoard
{
private:
	static ScoreBoard* instance; // 2. static private instance

	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 position, drawingPosition = D3DXVECTOR3(0, 0, 0);
	unordered_map<string, RECT> frames;

	int width, height;

	long startTime;
	int time, point, coin, marioLife, momentum;
	int momentumX, momentumY, marioLifeX, marioLifeY, coinX, coinY, pointX, pointY, timeX, timeY;
public:
	ScoreBoard(const ScoreBoard&) = delete; // 3. delete copy constructor
	static ScoreBoard* getInstance();	  // 4. public function for client code usage

	// Init
	ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor);

	// Getter
	int getTime();
	int getWidth();
	int getHeight();
	int getMomentumLevel(int _momentum, int _space);
	string getMomentumKey(int _momentumLevel);

	// Setter
	void setTime(int _time);
	void plusPoint(int _value);
	void plusCoin(int _value);
	void minusMarioLife(); // it will minus mario's life to 1
	void resetTimeToZero();
	void resetTimeTo300();
	void setMomentum(int _momentum);


	RECT getFrame(string keyword);

	void load();
	void loadInfo(string line, char seperator);
	void loadFrames(vector<string> data, char keywordSeperator, char seperator);

	void Update(float _dt);
	void Draw();
	void DrawMarioLife();
	void DrawCoin();
	void DrawPoint();
	void DrawTime();
	void DrawMomentum();
};

