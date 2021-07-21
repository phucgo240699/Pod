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
	this->isFakeGoldenBrick = v[5] == 1;
	this->setGiftType(v[6]);

	// Box
	this->endBoxJumpUp = this->getY() - 12;
	this->beginBoxJumpUp = this->getY();

	// Super mushroom
	if (this->getGiftType() == GiftType::SuperMushroomOrSuperLeaf) {
		superMushroom = new SuperMushroom(this->getX(), this->getY(), v[7], v[8], v[9], v[10], v[11]);
		superLeaf = new SuperLeaf(this->getX(), this->getY(), v[12], v[13], v[14], v[15], v[16]);

		superMushroom->setDefaultPoints(v[17]);
		superLeaf->setDefaultPoints(v[18]);
		return;
	}
	else if (this->getGiftType() == GiftType::SuperMushroomGift) {
		superMushroom = new SuperMushroom(this->getX(), this->getY(), v[7], v[8], v[9], v[10], v[11]);
		superMushroom->setIsGreenMode(v[12] == 1);
	}
	else if (this->getGiftType() == GiftType::MultiCoinGift) {

	}

	// Coin
	this->coinY = this->getY() - 16;
	this->beginCoinJumpUp = this->getY() - 16;
	this->endCoinJumpUp = this->getY() - 48;

	// Points
	this->pointY = this->getY() - 16;
}

SuperMushroom* GiftBrick::getSuperMushroom()
{
	return this->superMushroom;
}

SuperLeaf* GiftBrick::getSuperLeaf()
{
	return this->superLeaf;
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

void GiftBrick::setSuperLeafState(SuperLeafState _state)
{
	this->superLeaf->setState(_state);
}

void GiftBrick::setState(GiftBrickState _state)
{
	switch (_state)
	{
	case FULLGIFTBRICK:
		if (this->getState() != FULLGIFTBRICK || this->boxAnimation == NULL) {
			if (this->isFakeGoldenBrick) {
				this->boxAnimation = new Animation(AnimationBundle::getInstance()->getGoldenBrick());
			}
			else {
				this->boxAnimation = new Animation(AnimationBundle::getInstance()->getFullGiftBrick());
			}
			this->state = _state;
		}
		break;
	case POPUPGIFTBRICK:
		if (this->getState() == FULLGIFTBRICK) {
			
			if (this->getGiftType() == SuperLeafGift) {
				// add super leaf to grid
				Grid::getInstance()->add(this->superLeaf);
				Grid::getInstance()->updateCellOf(this->superLeaf);
			}

			//delete boxAnimation;
			if (this->getGiftType() != GiftType::MultiCoinGift) {
				this->boxAnimation = new Animation(AnimationBundle::getInstance()->getEmptyGiftBrick());
			}
			if (this->getGiftType() == Point100Gift) {
				this->coinAnimation = new Animation(AnimationBundle::getInstance()->getCoinGiftBrick());
				this->pointAnimation = new Animation(AnimationBundle::getInstance()->get100Points());
			}
			this->state = _state;
		}
		break;
	case EMPTYGIFTBRICK:
		if (this->getState() == POPUPGIFTBRICK) {
			//this->boxAnimation = new Animation(AnimationBundle::getInstance()->getEmptyGiftBrick());
			/*delete coinAnimation;
			delete pointAnimation;*/
			this->state = _state;
		}
		break;
	default:
		break;
	}
}

void GiftBrick::setGiftType(GiftType _giftType)
{
	this->giftType = _giftType;
}

void GiftBrick::setGiftType(int _giftCode)
{
	if (_giftCode == 0) {
		this->giftType = GiftType::SuperMushroomOrSuperLeaf;
	}
	else if (_giftCode == 1) {
		this->giftType = GiftType::Point100Gift;
	}
	else if (_giftCode == 2) {
		this->giftType = GiftType::SuperMushroomGift;
	}
	else {
		this->giftType = GiftType::MultiCoinGift;
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
				if (this->getGiftType() != Point100Gift) {
					this->setState(GiftBrickState::EMPTYGIFTBRICK);
				}
				if (this->getGiftType() == SuperMushroomGift) {
					Grid::getInstance()->add(this->superMushroom);
					Grid::getInstance()->updateCellOf(this->superMushroom);
					return;
				}
			}
		}

		if (this->getGiftType() == Point100Gift) {

			// Coin
			this->coinAnimation->Update(_dt);

			if (isCoinDropDown == false) {
				if (this->coinY - 3 >= endCoinJumpUp) {
					this->coinY -= 3;
				}
				else {
					isCoinDropDown = true;
					this->coinY = endCoinJumpUp;
				}
			}
			else {
				if (this->coinY + 3 <= beginCoinJumpUp) {
					this->coinY += 3;
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