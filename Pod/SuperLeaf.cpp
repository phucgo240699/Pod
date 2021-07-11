#include "SuperLeaf.h"

SuperLeaf::SuperLeaf(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id) : Component(_x, _y, _vx, _vy, 0, 0, _id)
{
	Component::Component(_x, _y, _vx, _vy, 0, 0, _id);
	this->setWidth(_width);
	this->setHeight(_height);

}

SuperLeafState SuperLeaf::getState()
{
	return this->state;
}

void SuperLeaf::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void SuperLeaf::setState(SuperLeafState _state)
{
	this->state = _state;
}

void SuperLeaf::Update(float _dt)
{
}

void SuperLeaf::Draw(LPDIRECT3DTEXTURE9 _texture)
{
}
