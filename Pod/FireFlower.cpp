#include "FireFlower.h"
#include "Camera.h"
#include "Mario.h"

FireFlower::FireFlower(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originVy = _vy;
}

FireFlowerState FireFlower::getState()
{
	return this->state;
}

int FireFlower::getCountDown()
{
	return this->countDown;
}

bool FireFlower::getIsFlip()
{
	return this->isFlip;
}

bool FireFlower::getIsGreenMode()
{
	return this->isGreenMode;
}

bool FireFlower::getIsHalfSizeMode()
{
	return this->isHalfSizeMode;
}

float FireFlower::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float FireFlower::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float FireFlower::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireFlower::getBoundsHeight()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireFlower::getTopAnchor()
{
	return this->topAnchor;
}

float FireFlower::getBottomAnchor()
{
	return this->bottomAnchor;
}

float FireFlower::getLeftAnchor()
{
	return this->leftAnchor;
}

float FireFlower::getRightAnchor()
{
	return this->rightAnchor;
}

//FireFlowerBall* FireFlower::getFireFlowerBall()
//{
//	return this->fireFlowerBall;
//}

void FireFlower::setState(FireFlowerState _state)
{
	switch (_state)
	{
	case FIRE_FLOWER_STANDING_LOOK_DOWN:
	{
		delete animation;
		if (this->getIsHalfSizeMode()) {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookDownHalfSize());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookDownHalfSize());
			}
		}
		else {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookDown());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookDown());
			}
		}
		this->setVy(0);
		break;
	}
	case FIRE_FLOWER_STANDING_LOOK_UP:
	{
		delete animation;
		if (this->getIsHalfSizeMode()) {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookUpHalfSize());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookUpHalfSize());
			}
		}
		else {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookUp());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookUp());
			}
		}
		this->setVy(0);
		break;
	}
	case FIRE_FLOWER_GROWING_UP:
	{
		delete animation;
		if (this->getIsHalfSizeMode()) {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerGrowingUpHalfSize());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerGrowingUpHalfSize());
			}
		}
		else {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerGrowingUp());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerGrowingUp());
			}
		}
		this->setVy(-abs(this->originVy));
		this->countDown = 80;
		break;
	}
	case FIRE_FLOWER_DROPPING:
	{
		delete animation;
		if (this->getIsHalfSizeMode()) {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerDroppingHalfSize());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerDroppingHalfSize());
			}
		}
		else {
			if (this->getIsGreenMode()) {
				this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerDropping());
			}
			else {
				this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerDropping());
			}
		}
		this->setVy(abs(this->originVy));
		//this->countDown = 120;
		break;
	}
	case FIRE_FLOWER_HIDING:
		if (this->animation == NULL) {
			if (this->getIsHalfSizeMode()) {
				if (this->getIsGreenMode()) {
					this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookDownHalfSize());
				}
				else {
					this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookDownHalfSize());
				}
			}
			else {
				if (this->getIsGreenMode()) {
					this->animation = new Animation(AnimationBundle::getInstance()->getGreenFireFlowerStandingLookDown());
				}
				else {
					this->animation = new Animation(AnimationBundle::getInstance()->getRedFireFlowerStandingLookDown());
				}
			}
		}
		this->setVy(0);
		this->countDown = 120;
	default:
		break;
	}
	this->state = _state;
}

void FireFlower::setFireFlowerBall(FireFlowerBallState _fireFlowerBallState)
{
	this->fireFlowerBall->setState(_fireFlowerBallState);
}

void FireFlower::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void FireFlower::setIsGreenMode(bool _isGreenMode)
{
	this->isGreenMode = _isGreenMode;
}

void FireFlower::setIsHalfSizeMode(bool _isHalfSizeMode)
{
	isHalfSizeMode = _isHalfSizeMode;
}

void FireFlower::reduceCountDown()
{
	this->countDown -= 1;
}

void FireFlower::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVy(v[2]);
	this->originVy = v[2];
	this->topAnchor = v[3];
	this->bottomAnchor = v[4];
	this->leftAnchor = v[5];
	this->rightAnchor = v[6];
	this->setIsHalfSizeMode(v[7] == 1);
	this->setIsGreenMode(v[8] == 1);
	this->setId(v[9]);

	this->fireFlowerBall = new FireFlowerBall(v[10], v[11], v[12], v[13], Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), v[14]);
}

void FireFlower::Update(float _dt)
{
	if (this->getState() == FIRE_FLOWER_GROWING_UP && this->getY() + this->getVy() * _dt < topAnchor) {
		this->setY(this->topAnchor);
		this->setState(FireFlowerState::FIRE_FLOWER_STANDING_LOOK_DOWN);
		return;
	}
	else if (this->getState() == FIRE_FLOWER_STANDING_LOOK_DOWN) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_DROPPING);

			this->fireFlowerBall->setX(this->getX() + this->getWidth() / 2);
			this->fireFlowerBall->setY(this->getY() + this->getWidth() / 2);
			Grid::getInstance()->add(this->fireFlowerBall);
			//Grid::getInstance()->updateCellOf(this->fireFlowerBall);
			if (this->getIsFlip()) {
				this->fireFlowerBall->setState(FireFlowerBallState::FIRE_FLOWER_BALL_FLYING_LOWER_LEFT);
			}
			else {
				this->fireFlowerBall->setState(FireFlowerBallState::FIRE_FLOWER_BALL_FLYING_LOWER_RIGHT);
			}

			return;
		}
		this->countDown -= 1;
	}
	else if (this->getState() == FIRE_FLOWER_STANDING_LOOK_UP) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_DROPPING);

			this->fireFlowerBall->setX(this->getX() + this->getWidth() / 2);
			this->fireFlowerBall->setY(this->getY() + this->getWidth() / 2);
			Grid::getInstance()->add(this->fireFlowerBall);
			//Grid::getInstance()->updateCellOf(this->fireFlowerBall);
			if (this->getIsFlip()) {
				this->fireFlowerBall->setState(FireFlowerBallState::FIRE_FLOWER_BALL_FLYING_UPPER_LEFT);
			}
			else {
				this->fireFlowerBall->setState(FireFlowerBallState::FIRE_FLOWER_BALL_FLYING_UPPER_RIGHT);
			}
			return;
		}
		this->countDown -= 1;
	}

	else if (this->getState() == FIRE_FLOWER_DROPPING && this->getY() + this->getVy() * _dt > bottomAnchor) {
		this->setY(this->bottomAnchor);
		this->setState(FireFlowerState::FIRE_FLOWER_HIDING);
		return;
	}
	else if (this->getState() == FIRE_FLOWER_HIDING) {
		if (countDown <= 0) {
			this->setState(FireFlowerState::FIRE_FLOWER_GROWING_UP);
			return;
		}
		this->countDown -= 1;
	}

	this->animation->Update(_dt);
	this->plusYNoRound(this->getVy() * _dt);
}

void FireFlower::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition(), this->getIsFlip());
}

void FireFlower::handleMarioCollision(Mario* _mario, float _dt)
{
	if (this->getState() == FIRE_FLOWER_HIDING) return;
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) {
		_mario->setState(MarioState::DIE);
	}
}
