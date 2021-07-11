#pragma once
#include "Animation.h"
#include "AnimationBundle.h"

class AnimationCD
{
protected:
	Animation animation = Animation(0, 0, 0);

	D3DXVECTOR3 position;
	bool isFinish = false;
public:
	// Init
	AnimationCD(Animation _animation);
	//AnimationCD();

	// Getter
	bool getIsFinish();
	
	// Setter
	void setIsFinish(bool _isFinish);

	virtual void Update(float _dt);
	virtual void Draw(LPDIRECT3DTEXTURE9 _texture);
};

