#pragma once
#include "Animation.h"

class MarioStandingLeft : public Animation
{
public:
	// Init
	MarioStandingLeft(int _id, int _indexFrame, int _animDelay);
	MarioStandingLeft(int _id, int _indexFrame, int _animDelay, vector<RECT*>* _frames);
	MarioStandingLeft(int _id, int _indexFrame, int _animDelay, string filePath);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3* _position, D3DCOLOR _color);
};

