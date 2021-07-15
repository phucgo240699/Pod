#pragma once
#include "Component.h"
#include "FireFlowerState.h"
#include "AnimationBundle.h"

class FireFlower : public Component
{
private:
	Animation* animation;
	FireFlowerState state;
	float originVy;
	float topAnchor, bottomAnchor;
	int countDown = 120;
	bool isFlip = false;

public:
	// Init
	FireFlower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FireFlowerState getState();
	int getCountDown();
	bool getIsFlip();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();

	// Setter
	void setState(FireFlowerState _state);
	void setIsFlip(bool _isFlip);

	void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

};