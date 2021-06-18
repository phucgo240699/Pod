#pragma once
#include "Component.h"
#include "Camera.h"
#include "GiftBrickState.h"

class GiftBrick : public Component
{
private:
	GiftBrickState state = FULL;
	Animation* animation;
public:
	GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	GiftBrick(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	//void loadAnimation(vector<string> data);
	void setAnimation(Animation* _animaiton);
	void loadInfo(string line, char seperator);

	// Getter
	GiftBrickState getState();
	//Animation* getAnimation();

	// Setter
	void setState(GiftBrickState _state);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

