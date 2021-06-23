#pragma once
#include "Enemy.h"
#include "GoombaState.h"
#include "AnimationBundle.h"
#include "Camera.h"
#include "Grid.h"

class Goomba : public Enemy
{
private:
	Animation* animation;
	GoombaState state;

public:
	// Init
	Goomba(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Goomba(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	GoombaState getState();

	// Setter
	void setState(GoombaState _state);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

