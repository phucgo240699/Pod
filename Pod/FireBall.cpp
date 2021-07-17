#include "FireBall.h"

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
	if (this->getState() == FIREBALL_STAYING && this->getState() == FIREBALL_DISAPPEARED)  return;
	
	this->plusXNoRound(this->getVx() * _dt);
	if (this->getY() + this->getVy() * _dt < this->topAnchor) {
		this->setY(this->topAnchor);
		this->setIsGoDown(true);
	}
	else {
		this->plusYNoRound(this->getVy() * _dt);
	}
}

void FireBall::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == FIREBALL_STAYING && this->getState() == FIREBALL_DISAPPEARED)  return;

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void FireBall::setTopAnchor(bool _topAnchor)
{
	this->topAnchor = _topAnchor;
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
		else if (edge == topEdge) {
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setIsGoDown(true);
			this->topAnchor = this->getY();
		}
		else if (edge == leftEdge || edge == rightEdge) {
			this->plusX(get<1>(collisionResult) * this->getVx());
			this->plusY(get<1>(collisionResult) * this->getVy());
			this->setState(FireBallState::FIREBALL_DISAPPEARED);
			AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), this->getX(), this->getY())));
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

		this->setState(FireBallState::FIREBALL_DISAPPEARED);
		ScoreBoard::getInstance()->plusPoint(_goomba->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_goomba->getDefaultPoint(), _goomba->getX(), _goomba->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), this->getX(), this->getY())));
	}
}

void FireBall::handleKoopaCollision(Koopa* _koopa, float _dt)
{
	if (_koopa->getState() == KOOPA_THROWN_LEFT_AWAY || _koopa->getState() == KOOPA_THROWN_RIGHT_AWAY) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_koopa, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_koopa->getBounds())) {
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());

		_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
		_koopa->plusX(get<1>(collisionResult) * _koopa->getVx());
		if (this->getState() == FIREBALL_FLYING_LEFT) {
			_koopa->setState(KoopaState::KOOPA_THROWN_LEFT_AWAY);
		}
		else if (this->getState() == FIREBALL_FLYING_RIGHT) {
			_koopa->setState(KoopaState::KOOPA_THROWN_RIGHT_AWAY);
		}

		this->setState(FireBallState::FIREBALL_DISAPPEARED);
		ScoreBoard::getInstance()->plusPoint(2 * _koopa->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(2 * _koopa->getDefaultPoint(), _koopa->getX(), _koopa->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), this->getX(), this->getY())));
	}
}

void FireBall::handleFireFlowerCollision(FireFlower* _fireFlower, float _dt)
{
	if (this->getState() == FIRE_FLOWER_DEAD || _fireFlower->getState() == FIRE_FLOWER_HIDING) return;
	if (_fireFlower->getState() == FIRE_FLOWER_GROWING_UP || _fireFlower->getState() == FIRE_FLOWER_DROPPING) {
		if (this->getY() + this->getVy() * _dt >= _fireFlower->getBottomAnchor()) return;
	}
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_fireFlower, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_fireFlower->getBounds())) {
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());
		this->setState(FireBallState::FIREBALL_DISAPPEARED);

		_fireFlower->plusX(get<1>(collisionResult) * _fireFlower->getVx());
		_fireFlower->plusX(get<1>(collisionResult) * _fireFlower->getVx());
		_fireFlower->setState(FireFlowerState::FIRE_FLOWER_DEAD);

		ScoreBoard::getInstance()->plusPoint(_fireFlower->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_fireFlower->getDefaultPoint(), _fireFlower->getX(), _fireFlower->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), this->getX(), this->getY())));
	}
}

void FireBall::handleFlowerCollision(Flower* _flower, float _dt)
{
	if (_flower->getState() == FLOWER_DEAD || _flower->getState() == FLOWER_HIDING || _flower->getState() == FLOWER_STANDING) return;
	if (_flower->getState() == FLOWER_GROWING_UP || _flower->getState() == FLOWER_DROPPING) {
		if (this->getY() + this->getVy() * _dt >= _flower->getBottomAnchor()) return;
	}

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_flower, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_flower->getBounds())) {
		this->plusX(get<1>(collisionResult) * this->getVx());
		this->plusY(get<1>(collisionResult) * this->getVy());
		this->setState(FireBallState::FIREBALL_DISAPPEARED);

		_flower->plusX(get<1>(collisionResult) * _flower->getVx());
		_flower->plusX(get<1>(collisionResult) * _flower->getVx());
		_flower->setState(FlowerState::FLOWER_DEAD);

		ScoreBoard::getInstance()->plusPoint(_flower->getDefaultPoint());
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(_flower->getDefaultPoint(), _flower->getX(), _flower->getY())));
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::FlashLightCDType, new FlashLightCD(Animation(AnimationBundle::getInstance()->getFireBallSplash()), this->getX(), this->getY())));
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