#pragma once
#include "MarioState.h"
#include "KeyType.h"
#include "Camera.h"
#include "Animation.h"
#include "MainCharacter.h"
#include <unordered_map>

using namespace std;

class Mario : public MainCharacter
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	MarioSubState subState;
	bool isFlip; // false: Left side - true: Right side. Default is false
	bool debugMode = true;

	vector<Animation*>* animations;
	Animation* currentAnimation;

	//void setUpAnimations();

public:
	float startdrop = 0;
	// Init
	Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// De Init
	~Mario();

	// Getter
	Animation* getCurrentAnimation();
	MarioSubState getSubState();
	MarioState getState();
	RECT* getBounds();
	bool getIsFlip();
	float getWidth();
	float getHeight();


	// Setter
	void setIsFlip(bool _isFlip);
	void setState(MarioState _state);
	void setSubState(MarioSubState _subState);
	void updateVelocity();

	// Inherit
	void Update(float _dt);
	void Draw();

	// Keyboard
	void onKeyUp();
	void onKeyUp(vector<KeyType> _keyTypes);
	void onKeyDown(vector<KeyType> _keyTypes);

	void loadInfo(string line, char seperator);
	void loadAnimations(vector<string> data, char seperatorRow, char seperatorCol);
};

