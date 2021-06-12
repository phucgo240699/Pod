#pragma once
#include "MainCharacter.h"
#include "WMarioState.h"

class WMario : public MainCharacter
{
private:
	Animation* animation;
	vector<vector<char>> movingMatrix;
	WMarioState state = WMARIO_STANDING;

	int tileSize, row, col, borderWidth;
	int startRowMove, startColMove;
	bool isMoving = false;
	char limitScenceId = 'A';
	char limitSceneMoving = '1';
public:
	WMario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	WMario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	// Getter
	float getWidth();
	float getHeight();
	WMarioState getState();
	char getCurrentSceneId();

	// Setter
	void setState(WMarioState _state);

	// Inherit
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	void onKeyDown(vector<KeyType> _keyTypes);

	void loadInfo(string line, char seperator);
	void loadAnimations(vector<string> data, char seperatorRow, char seperatorCol);
	void loadMovingMatrix(vector<string> data, char seperator);

	// Check methods
	bool canMoveRight();
	bool canMoveLeft();
	bool canMoveTop();
	bool canMoveBottom();
};

