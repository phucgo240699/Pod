#include "GiftBrick.h"

//Animation* GiftBrick::getAnimation()
//{
//	return this->animation;
//}

GiftBrick::GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GiftBrick::GiftBrick(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void GiftBrick::setAnimation(Animation* _animaiton)
{
	this->animation = new Animation(*_animaiton);
}

void GiftBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVy(v[3]);
	this->topAnchor = this->getY() - 12;
}

GiftBrickState GiftBrick::getState()
{
	return this->state;
}



void GiftBrick::setState(GiftBrickState _state)
{
	this->state = _state;
	switch (_state)
	{
	case FULL:
		this->animation = new Animation(*AnimationBundle::getInstance()->getAnimationAt(0));
		break;
	case POPUP:
	case EMPTY:
		this->animation = new Animation(*AnimationBundle::getInstance()->getAnimationAt(1));
		break;
	default:
		break;
	}
}

void GiftBrick::Update(float _dt)
{
	//switch (state)
	//{
	//case FULL:
	//	this->animation->Update(_dt);
	//	break;
	//case POPUP:
	//	if (this->getY() - 1 >= topAnchor) {
	//		this->plusY(-1);
	//	}
	//	/*if (this->animation->getCurrentIndexFrame() == this->animation->getTotalFrames() - 1) {
	//		this->setState(GiftBrickState::EMPTY);
	//	}*/
	//	break;
	//case EMPTY:
	//	this->animation->Update(_dt);
	//	break;
	//default:
	//	break;
	//}
}

void GiftBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{

	//switch (state)
	//{
	//case FULL:
	//	/*D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	//	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);
	//	break;*/
	//case POPUP:
	//	D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	//	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);
	//	break;
	//case EMPTY:
	//	break;
	//default:
	//	break;
	//}
	/*D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);*/
}
