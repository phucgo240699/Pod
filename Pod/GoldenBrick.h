#pragma once
#include "Component.h"
#include "Camera.h"
#include "AnimationBundle.h"
#include "GoldenBrickState.h"
#include "PButton.h"

class Grid;

class GoldenBrick : public Component
{
private:
	Animation* animation;
	GoldenBrickState state;
	PButton* pButton;

	bool hasPButton;

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

