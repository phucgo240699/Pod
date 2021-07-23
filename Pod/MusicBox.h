#pragma once
#include "Component.h"
#include "MusicBoxState.h"

class MusicBox : public Component
{
private:
	Animation* animation;
	MusicBoxState state;
	
	bool isSpecial = false, isTransparentMode = false;
	float originX, originY, jumpSpace = 6, jumpSpeed = 2;
	bool isJumpingUp, isJumpingDown, isJumpingLeft, isJumpingRight;

public:
	// Init
	MusicBox(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);

	// Getter
	bool getIsSpecial();
	float getOriginX();
	float getOriginY();
	bool getIsTransparentMode();
	MusicBoxState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();

	void setOriginX(float _originX);
	void setOriginY(float _originY);
	void setIsTransparentMode(bool _value);
	void setIsSpecial(bool _value);
	void setAnimation(Animation* _animation);
	void setState(MusicBoxState _state);

	void loadInfo(string line, char seperator);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

