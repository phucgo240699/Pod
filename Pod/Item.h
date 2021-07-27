#pragma once
#include "Component.h"
#include "ItemState.h"

class Item : public Component
{
private:
	Animation* animation;
	ItemState state;

public:
	// Init
	Item(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	ItemState getState();
	int getWidth();
	int getHeight();
	int getBoundsWidth();
	int getBoundsHeight();
	Animation* getAnimation();

	// Setter
	void setState(ItemState _state);
	void setAnimation(Animation* _animation);

	void loadInfo(string line, char seperator);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

