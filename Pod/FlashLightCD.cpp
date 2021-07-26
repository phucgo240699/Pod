#include "FlashLightCD.h"

FlashLightCD::FlashLightCD(Animation _animation, float _x, float _y) : AnimationCD(_animation)
{
	AnimationCD::AnimationCD(_animation);
	this->position.x = _x;
	this->position.y = _y;
}

FlashLightCD::FlashLightCD(float _x, float _y) : AnimationCD(Animation(AnimationBundle::getInstance()->getFlashLight()))
{
	AnimationCD::AnimationCD(Animation(AnimationBundle::getInstance()->getFlashLight()));
	this->position.x = _x;
	this->position.y = _y;
}

void FlashLightCD::Update(float _dt)
{
	this->animation.Update(_dt);
	if (this->animation.getCurrentIndexFrame() >= this->animation.getTotalFrames() - 1) {
		this->setIsFinish(true);
	}
}

void FlashLightCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	this->animation.Draw(_texture, this->animation.getCurrentFrame(), this->position);
}
