#pragma once
#include "Component.h"
#include "Camera.h"

class GiftBrick : public Component
{
private:
	Animation* animation;
public:
	GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	GiftBrick(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	void loadAnimation(vector<string> data);
	void loadInfo(string line, char seperator);

	// Getter
	Animation* getAnimation();

	// Setter

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

