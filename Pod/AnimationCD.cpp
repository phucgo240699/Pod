#include "AnimationCD.h"

AnimationCD::AnimationCD(Animation* _animation)
{
    this->animation = _animation;
}

bool AnimationCD::getIsFinish()
{
    return this->isFinish;
}

void AnimationCD::setIsFinish(bool _isFinish)
{
    this->isFinish = _isFinish;
}

void AnimationCD::Update(float _dt)
{
}

void AnimationCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
}
