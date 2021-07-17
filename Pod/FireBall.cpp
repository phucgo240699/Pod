#include "FireBall.h"
#include "Block.h"
#include "Goomba.h"

FireBall::FireBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY, _id)
{
	Component::Component(_x, _y, _vx, _vy, _limitX, _limitY, _id);
	this->originX = _x;
	this->originY = _y;
	this->originVx = _vx;
	this->originVy = _vy;
}

FireBallState FireBall::getState()
{
	return this->state;
}

float FireBall::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float FireBall::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

float FireBall::getBoundsWidth()
{
	return this->animation->getCurrentBoundsWidth();
}

float FireBall::getBoundsHeight()
{
	return this->animation->getCurrentBoundsHeight();
}

bool FireBall::getIsOutOfGrid()
{
	return this->isOutOfGrid;
}

bool FireBall::getIsGoDown()
{
	return this->isGoDown;
}

void FireBall::setState(FireBallState _state)
{
	switch (_state)
	{
	case FIREBALL_STAYING:
		this->setVx(0);
		break;
	case FIREBALL_FLYING_LEFT:
		this->setVx(-abs(this->originVx));
		break;
	case FIREBALL_FLYING_RIGHT:
		this->setVx(abs(this->originVx));
		break;
	default:
		break;
	}
	this->state = _state;
}

void FireBall::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void FireBall::resetToOriginalPosition()
{
	this->setX(this->originX);
	this->setY(this->originY);
}

void FireBall::setIsOutOfGrid(bool _isOutOfGrid)
{
	this->isOutOfGrid = _isOutOfGrid;
}

void FireBall::setIsGoDown(bool _isGoDown)
{
	this->isGoDown = _isGoDown;
	if (_isGoDown) {
		this->setVy(abs(originVy));
	}
	else {
		this->setVy(-abs(originVy));
	}
}

void FireBall::Update(float _dt)
{
	if (this->getState() != FIREBALL_STAYING) {
		this->plusXNoRound(this->getVx() * _dt);
		if (this->getY() + this->getVy() * _dt < this->topAnchor) {
			this->setY(this->topAnchor);
			this->setIsGoDown(true);
		}
		else {
			this->plusYNoRound(this->getVy() * _dt);
		}
	}
}

void FireBall::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() != FIREBALL_STAYING) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
	}
}

void FireBall::handleHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == bottomEdge) {
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setIsGoDown(false);
			this->topAnchor = this->getY() - 16;
		}
	}
}

void FireBall::handleGoombaCollision(Goomba* _goomba, float _dt)
{
	if (_goomba->getState() == TRAMPLED_GOOMBA
		|| _goomba->getState() == THROWN_LEFT_AWAY_GOOMBA
		|| _goomba->getState() == THROWN_RIGHT_AWAY_GOOMBA
		|| _goomba->getState() == DEAD_GOOMBA) {
		return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_goomba, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_goomba->getBounds())) {
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint() * _goomba->getPointCoef(), _goomba->getX(), _goomba->getY())));
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());
		_goomba->plusX(get<1>(collisionResult) * _goomba->getVx());
		_goomba->plusX(get<1>(collisionResult) * _goomba->getVx());
		
		if (this->getState() == FIREBALL_FLYING_LEFT) {
			_goomba->setState(THROWN_LEFT_AWAY_GOOMBA);
		}
		else if (this->getState() == FIREBALL_FLYING_RIGHT) {
			_goomba->setState(THROWN_RIGHT_AWAY_GOOMBA);
		}
	}
}

void FireBall::handleBlockCollision(Block* _block, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_block, _dt);

	if (get<0>(collisionResult) == true) {
		CollisionEdge edge = get<2>(collisionResult)[0];

		if (edge == bottomEdge) {
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setIsGoDown(false);
			this->topAnchor = this->getY() - 16;
		}
	}
}
