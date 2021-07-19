#include "GoldenBrick.h"
#include "Grid.h"

GoldenBrick::GoldenBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GoldenBrick::GoldenBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

GoldenBrickState GoldenBrick::getState()
{
	return this->state;
}

bool GoldenBrick::getHasPButton()
{
	return this->hasPButton;
}

PButton* GoldenBrick::getPButton()
{
	return this->pButton;
}

void GoldenBrick::setState(GoldenBrickState _state)
{
	switch (_state)
	{
	case GOLDEN_BRICK_STAYING:
		this->animation = new Animation(AnimationBundle::getInstance()->getGoldenBrick());
		break;
	case GOLDEN_BRICK_DISAPPEARED:
		break;
	case GOLDEN_BRICK_EMPTY:
		if (this->getState() != GOLDEN_BRICK_EMPTY) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getEmptyGiftBrick());
		}
		break;
	case GOLDEN_BRICK_BEING_COIN:
		if (this->getState() == GOLDEN_BRICK_STAYING) {
			delete animation;
			this->animation = new Animation(AnimationBundle::getInstance()->getCoin());
		}
	default:
		break;
	}
	this->state = _state;
}

void GoldenBrick::setHasPButton(bool _hasPButton)
{
	this->hasPButton = _hasPButton;
}

void GoldenBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setHasPButton(v[4] == 1);
	this->setId(v[5]);

	if (this->getHasPButton()) {
		this->pButton = new PButton(v[6], v[7], 0, 0, 0, 0, v[8]);
	}
}

void GoldenBrick::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void GoldenBrick::Update(float _dt)
{
	animation->Update(_dt);
}

void GoldenBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}
