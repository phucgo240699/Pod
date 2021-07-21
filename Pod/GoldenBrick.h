#pragma once
#include "Component.h"
#include "Camera.h"
#include "AnimationBundle.h"
#include "GoldenBrickState.h"
#include "PButton.h"
#include "SuperMushroom.h"

class Grid;

class GoldenBrick : public Component
{
private:
	Animation* animation;
	GoldenBrickState state;
	PButton* pButton;
	SuperMushroom* superMushroom;

	bool hasPButton;


	// For Fragments Animation
	float xLeft = 0, xRight = 0, originXLeft, originXRight;
	float y1 = 0, y2 = 0, y3 = 0, y4 = 0, originYTop, originYBottom;
	// 1	2
	// 3	4
	Animation* brickFragment1, * brickFragment2, * brickFragment3, * brickFragment4;
	bool isFinishFragmentAnimation = false, startFragmentAnimation = false;
	D3DXVECTOR3 drawingPos = D3DXVECTOR3(0, 0, 0);

public:
	// Init
	GoldenBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	GoldenBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	GoldenBrickState getState();
	bool getHasPButton();
	PButton* getPButton();


	// Setter
	void setState(GoldenBrickState _state);
	void setHasPButton(bool _hasPButton);


	void loadInfo(string line, char seperator);
	void setAnimation(Animation* _animation);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

