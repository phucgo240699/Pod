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

//void GiftBrick::setAnimation(Animation* _animaiton)
//{
//	this->animation = new Animation(*_animaiton);
//}

void GiftBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setId(v[4]);
	this->giftId = v[5];

	// Box
	this->endBoxJumpUp = this->getY() - 12;
	this->beginBoxJumpUp = this->getY();

	// Coin
	this->coinY = this->getY() - 16;
	this->beginCoinJumpUp = this->getY() - 16;
	this->endCoinJumpUp = this->getY() - 48;

	// Points
	this->pointY = this->getY() - 16;
}

int GiftBrick::getGiftId()
{
	return this->giftId;
}

GiftBrickState GiftBrick::getState()
{
	return this->state;
}



void GiftBrick::setState(GiftBrickState _state)
{
	switch (_state)
	{
	case FULLGIFTBRICK:
		if (this->getState() != FULLGIFTBRICK || this->boxAnimation == NULL) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getAnimationAt(0));
			this->state = _state;
		}
		break;
	case POPUPGIFTBRICK:
		if (this->getState() == FULLGIFTBRICK) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getAnimationAt(1));
			this->coinAnimation = new Animation(AnimationBundle::getInstance()->getAnimationAt(2));
			this->pointAnimation = new Animation(AnimationBundle::getInstance()->getAnimationAt(3));
			this->state = _state;
		}
		break;
	case EMPTYGIFTBRICK:
		if (this->getState() == POPUPGIFTBRICK) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getAnimationAt(1));
			this->coinAnimation = NULL;
			this->pointAnimation = NULL;
			this->state = _state;
		}
		break;
	default:
		break;
	}
}

void GiftBrick::Update(float _dt)
{
	this->boxAnimation->Update(_dt);

	if (this->getState() == POPUPGIFTBRICK) {
		this->coinAnimation->Update(_dt);

		// Box
		if (isBoxDropDown == false) {
			if (this->getY() - 2 >= endBoxJumpUp) {
				this->plusY(-2);

			}
			else {
				isBoxDropDown = true;
				this->setY(endBoxJumpUp);
			}
		}
		else {
			if (this->getY() + 2 <= beginBoxJumpUp) {
				this->plusY(2);
			}
			else {
				if (this->getY() != beginBoxJumpUp) {
					this->setY(beginBoxJumpUp);
				}
			}
		}

		// Coin
		if (isCoinDropDown == false) {
			if (this->coinY - 4 >= endCoinJumpUp) {
				this->coinY -= 4;
			}
			else {
				isCoinDropDown = true;
				this->coinY = endCoinJumpUp;
			}
		}
		else {
			if (this->coinY + 4 <= beginCoinJumpUp) {
				this->coinY += 4;
			}
			else {
				if (this->coinY != beginCoinJumpUp) {
					this->coinY = beginCoinJumpUp;
				}
				this->isPointsStartPopUp = true;
			}
		}

		if (isPointsStartPopUp) {
			if (this->pointY - 2 >= this->endCoinJumpUp) {
				this->pointY -= 2;
			}
			else {
				isPointsStartPopUp = false;
				this->pointY = endCoinJumpUp;
				this->setState(GiftBrickState::EMPTYGIFTBRICK);
			}
		}
	}

	
}

void GiftBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	Drawing::getInstance()->draw(_texture, this->boxAnimation->getCurrentFrame(), &position);

	if (this->getState() == POPUPGIFTBRICK) {
		if (isPointsStartPopUp == false) {
			D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->coinY - Camera::getInstance()->getY(), 0);
			Drawing::getInstance()->draw(_texture, this->coinAnimation->getCurrentFrame(), &position);
		}
		else {
			D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->pointY - Camera::getInstance()->getY(), 0);
			Drawing::getInstance()->draw(_texture, this->pointAnimation->getCurrentFrame(), &position);
		}
	}
}
