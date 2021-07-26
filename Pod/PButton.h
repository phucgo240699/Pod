#pragma once
#include "AnimationBundle.h"
#include "Component.h"
#include "PButtonState.h"


class PButton : public Component
{
private:
	Animation* animation;
	PButtonState state;

public:
	// Init
	PButton(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	PButtonState getState();
	int getWidth();
	int getHeight();

	// Setter
	void setState(PButtonState _state);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};