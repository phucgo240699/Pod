#pragma once
#include "Drawing.h"

class ScoreBoard
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3* position;
public:
	// Init
	ScoreBoard(LPCWSTR _imagePath, D3DCOLOR _transcolor);

	void loadPosition(string line, char seperator);
	void Update(float _dt);
	void Draw();
};

