#include "GoldenBrick.h"
#include "Grid.h"
#include "ScoreBoard.h"

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
	case GOLDEN_BRICK_DISAPPEARING:
		this->brickFragment1 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
		this->brickFragment2 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
		this->brickFragment3 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
		this->brickFragment4 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
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


	// For Fragments Animation
	this->originYTop = this->getY();
	this->originYBottom = this->getY() + (this->getHeight() / 2);
	this->originXLeft = this->getX();
	this->originXRight = this->getX() + (this->getWidth() / 2);

	this->setLimitY(Camera::getInstance()->getLimitY() - ScoreBoard::getInstance()->getHeight());
}

void GoldenBrick::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void GoldenBrick::Update(float _dt)
{
	Component::Update(_dt);

	animation->Update(_dt);

	if (this->getState() == GOLDEN_BRICK_DISAPPEARING && this->isFinishFragmentAnimation == false) {
		this->brickFragment1->Update(_dt);
		this->brickFragment2->Update(_dt);
		this->brickFragment3->Update(_dt);
		this->brickFragment4->Update(_dt);

		xLeft -= 2;
		xRight += 2;

		y1 = (-1 * (48 - (pow(xLeft + 24, 2) / 12)));
		y2 = (-1 * (48 - (pow(xRight - 24, 2) / 12)));
		y3 = (-1 * (32 - (pow(xLeft + 16, 2) / 8)));
		y4 = (-1 * (32 - (pow(xRight - 16, 2) / 8)));

		limitY = Camera::getInstance()->getLimitY() - ScoreBoard::getInstance()->getHeight();
		if (y1 > limitY && y2 > limitY && y3 > limitY && y4 > limitY) {
			this->isFinishFragmentAnimation = true;
		}
	}
}

void GoldenBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == GOLDEN_BRICK_DISAPPEARING && this->isFinishFragmentAnimation == false) {
		drawingPos.x = originXLeft + xLeft;
		drawingPos.y = originYTop + this->y1;
		Drawing::getInstance()->draw(_texture, this->brickFragment1->getCurrentFrame(), this->drawingPos);

		drawingPos.x = originXRight + xRight;
		drawingPos.y = originYTop + this->y2;
		Drawing::getInstance()->draw(_texture, this->brickFragment2->getCurrentFrame(), this->drawingPos);

		drawingPos.x = originXLeft + xLeft;
		drawingPos.y = originYBottom + this->y3;
		Drawing::getInstance()->draw(_texture, this->brickFragment3->getCurrentFrame(), this->drawingPos);

		drawingPos.x = originXRight + xRight;
		drawingPos.y = originYBottom + this->y4;
		Drawing::getInstance()->draw(_texture, this->brickFragment4->getCurrentFrame(), this->drawingPos);
	}

	if (this->getState() == GOLDEN_BRICK_DISAPPEARING || this->getState() == GOLDEN_BRICK_DEAD) return;
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}
