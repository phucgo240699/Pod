#include "GreenPipe.h"
#include "AnimationBundle.h"

GreenPipe::GreenPipe(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GreenPipe::GreenPipe(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

bool GreenPipe::getIsBlackMode()
{
	return this->isBlackMode;
}

bool GreenPipe::getIsDownMode()
{
	return this->isDownMode;
}

int GreenPipe::getFloorNumber()
{
	return this->floorNumber;
}

//void GreenPipe::setupAnimation()
//{
//	if (this->floorNumber == 2) {
//		if (this->getIsBlackMode()) {
//			if (this->getIsDownMode()) {
//				this->animation = new Animation(AnimationBundle::getInstance()->getBlackPipe2FloorDown());
//			}
//			else {
//				this->animation = new Animation(AnimationBundle::getInstance()->getGreenPipe2Floor());
//			}
//		}
//		else {
//			this->animation = new Animation(AnimationBundle::getInstance()->getGreenPipe2Floor());
//		}
//	}
//	else {
//		this->animation = new Animation(AnimationBundle::getInstance()->getGreenPipe3Floor());
//	}
//}

void GreenPipe::setIsBlackMode(bool _isBlackMode)
{
	this->isBlackMode = _isBlackMode;
}

void GreenPipe::setIsDownMode(bool _isDownMode)
{
	this->isDownMode = _isDownMode;
}

void GreenPipe::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void GreenPipe::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->floorNumber = v[4];
	this->setId(v[5]);
	this->setIsBlackMode(v[6] == 1);
	this->setIsDownMode(v[7] == 1);
}

void GreenPipe::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, animation->getCurrentFrame(), this->getPosition());
}
