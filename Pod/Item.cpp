#include "Item.h"

Item::Item(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
}

ItemState Item::getState()
{
	return this->state;
}

int Item::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int Item::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

int Item::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

int Item::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

Animation* Item::getAnimation()
{
	return this->animation;
}

void Item::setState(ItemState _state)
{
	this->state = _state;
}

void Item::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void Item::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setId(stoi(v[2]));
}

void Item::Update(float _dt)
{
	Component::Update(_dt);

	if (this->getState() == ITEM_DISAPPEARD) return;

	this->animation->Update(_dt);
}

void Item::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == ITEM_DISAPPEARD) return;

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}
