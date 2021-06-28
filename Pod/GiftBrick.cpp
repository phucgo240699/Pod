#include "GiftBrick.h"

GiftBrick::GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GiftBrick::GiftBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void GiftBrick::loadInfo(string line, char seperator)
{
	vector <float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setId(v[4]);
	this->setGiftType(v[5]);

	// Box
	this->endBoxJumpUp = this->getY() - 12;
	this->beginBoxJumpUp = this->getY();

	// Super mushroom
	if (this->getGiftType() == SuperMushroomGift) {
		superMushroom = new SuperMushroom(this->getX(), this->getY(), v[6], v[7], v[8], v[9], v[10], this->getY() - this->getHeight());
		return;
	}

	// Coin
	this->coinY = this->getY() - 16;
	this->beginCoinJumpUp = this->getY() - 16;
	this->endCoinJumpUp = this->getY() - 48;

	// Points
	this->pointY = this->getY() - 16;
}

GiftBrickState GiftBrick::getState()
{
	return this->state;
}

GiftType GiftBrick::getGiftType()
{
	return this->giftType;
}

void GiftBrick::setSuperMushroomState(SuperMushroomState _state)
{
	this->superMushroom->setState(_state);
}

void GiftBrick::setState(GiftBrickState _state)
{
	switch (_state)
	{
	case FULLGIFTBRICK:
		if (this->getState() != FULLGIFTBRICK || this->boxAnimation == NULL) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getFullGiftBrick());
			this->state = _state;
		}
		break;
	case POPUPGIFTBRICK:
		if (this->getState() == FULLGIFTBRICK) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getEmptyGiftBrick());
			if (this->getGiftType() == Point100Gift) {
				this->coinAnimation = new Animation(AnimationBundle::getInstance()->getCoin());
				this->pointAnimation = new Animation(AnimationBundle::getInstance()->get100Points());
			}
			this->state = _state;
		}
		break;
	case EMPTYGIFTBRICK:
		if (this->getState() == POPUPGIFTBRICK) {
			this->boxAnimation = new Animation(AnimationBundle::getInstance()->getEmptyGiftBrick());
			this->coinAnimation = NULL;
			this->pointAnimation = NULL;
			this->state = _state;
		}
		break;
	default:
		break;
	}
}

void GiftBrick::setGiftType(int _giftCode)
{
	if (_giftCode == 0) {
		this->giftType = GiftType::SuperMushroomGift;
	}
	else {
		this->giftType = GiftType::Point100Gift;
	}
}

void GiftBrick::Update(float _dt)
{
	// Box
	this->boxAnimation->Update(_dt);
	if (this->getState() == POPUPGIFTBRICK) {

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

				if (this->getGiftType() == SuperMushroomGift) {
					this->setState(GiftBrickState::EMPTYGIFTBRICK);
					Grid::getInstance()->add(this->superMushroom);
					return;
				}
			}
		}

		if (this->getGiftType() == SuperMushroomGift) return;

		// Coin
		this->coinAnimation->Update(_dt);

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

		// Point
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
	Drawing::getInstance()->draw(_texture, this->boxAnimation->getCurrentFrame(), this->getPosition());
	
	if (this->getState() == POPUPGIFTBRICK) {
		if (this->getGiftType() == Point100Gift) {
			if (isPointsStartPopUp == false) {
				Drawing::getInstance()->draw(_texture, this->coinAnimation->getCurrentFrame(), D3DXVECTOR3(this->getX(), this->coinY, 0));
			}
			else {
				Drawing::getInstance()->draw(_texture, this->pointAnimation->getCurrentFrame(), D3DXVECTOR3(this->getX(), this->pointY, 0));
			}
		}
	}
}