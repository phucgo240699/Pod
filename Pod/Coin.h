#pragma once
#include "AnimationCDPlayer.h"
#include "Component.h"
#include "CoinState.h"

class Mario;

class Coin : public Component
{
private:
	Animation* animation;
	CoinState state;

public:
	// Init
	Coin(float _x, float _y, float _width, float _height, float _vx, float _vy, float _limitX, float _limitY);

	// Getter
	CoinState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();


	// Setter
	void setState(CoinState _state);
	void setAnimation(Animation* _animation);

	void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleMarioCollision(Mario* _mario, float _dt);
};

