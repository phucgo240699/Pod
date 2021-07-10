#pragma once
#include "Animation.h"

class AnimationCD
{
protected:
	Animation* animation;
	bool isFinish = false;
public:
	// Init
	AnimationCD(Animation* _animation);

	// Getter
	bool getIsFinish();
	
	// Setter
	void setIsFinish(bool _isFinish);

	virtual void Update(float _dt);
	virtual void Draw(LPDIRECT3DTEXTURE9 _texture);
};

