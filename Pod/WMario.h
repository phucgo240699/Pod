#pragma once
#include "MainCharacter.h"
#include "WMarioState.h"

class WMario : public MainCharacter
{
private:
	Animation* animation;
	vector<vector<char>> movingMatrix;
	WMarioState state = STAND;

	int tileSize, r, c;
	bool isMoving = false;
	char limitScenceId = '1';
public:
	WMario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	WMario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	// Getter
	float getWidth();
	float getHeight();
	WMarioState getState();

	// Setter
	void setState(WMarioState _state);

	// Inherit
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	void onKeyDown(vector<KeyType> _keyTypes);
	void onKeyUp();

	void loadInfo(string line, char seperator);
	void loadAnimations(vector<string> data, char seperatorRow, char seperatorCol);
	void loadMovingMatrix(vector<string> data, char seperator);
};

