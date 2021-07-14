#include "SuperMushroom.h"
#include "Block.h"
#include "Mario.h"

SuperMushroom::SuperMushroom(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id) : Component(_x, _y, _vx, _vy, 0, 0)
{
	Component::Component(_x, _y, _vx, _vy, 0, 0);
	this->setId(_id);
	this->setWidth(_width);
	this->setHeight(_height);
	this->endGrowUpY = this->getY() - this->getHeight();

	// Random number
	srand(time(NULL));

	int randomNumber = rand() % 2 + 1;
	this->moveLeftFirst = randomNumber == 1 ? true : false;
}

SuperMushroomState SuperMushroom::getState()
{
	return this->state;
}

bool SuperMushroom::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

void SuperMushroom::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void SuperMushroom::setState(SuperMushroomState _state)
{
	switch (_state)
	{
	case SUPER_MUSHROOM_GROWING_UP:
	{
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
		}
		this->setVy(-1 * abs(this->getVy()));
		break;
	}
	case SUPER_MUSHROOM_MOVING_LEFT:
	{
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
		}
		this->setVx(-1 * abs(this->getVx()));
		break;
	}
	case SUPER_MUSHROOM_MOVING_RIGHT:
	{
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
		}
		this->setVx(abs(this->getVx()));
		break;
	}
	case SUPER_MUSHROOM_DROPPING_LEFT:
	{
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
		}
		this->setVx(-abs(this->getVx()));
		this->setVy(abs(this->getVy()));
		break;
	}
	case SUPER_MUSHROOM_DROPPING_RIGHT:
	{
		if (animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
		}
		this->setVx(abs(this->getVx()));
		this->setVy(abs(this->getVy()));
		break;
	}
	case SUPER_MUSHROOM_BEING_EARNED:
	{
		//delete animation;
		break;
	}
	default:
		break;
	}
	this->state = _state;
}

void SuperMushroom::setIsStandOnSurface(bool _isStandOnSurface)
{
	this->isStandOnSurface = _isStandOnSurface;
}

void SuperMushroom::Update(float _dt)
{
	if (this->getState() == SUPER_MUSHROOM_DISAPPEARED) return;
	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}

	if (this->getState() == SUPER_MUSHROOM_GROWING_UP) {
		if (this->getY() + (this->getVy() * _dt) < this->endGrowUpY) {
			if (moveLeftFirst) {
				this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_LEFT);
				this->setIsStandOnSurface(true);
				return;
			}
			else {
				this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_RIGHT);
				this->setIsStandOnSurface(true);
				return;
			}
		}
		this->plusY(this->getVy()* _dt);
		this->animation->Update(_dt);
	}
	else if (this->getState() == SUPER_MUSHROOM_MOVING_LEFT || this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
		this->plusX(this->getVx() * _dt);
		this->animation->Update(_dt);
	}
	else if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT || this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
		this->plusXNoRound(0.5 * this->getVx() * _dt);
		this->plusYNoRound(1.5 * this->getVy() * _dt);
		this->animation->Update(_dt);
	}

	else if (this->getState() == SUPER_MUSHROOM_BEING_EARNED) {		
		AnimationCDPlayer::getInstance()->addCD(make_pair(CDType::PointUpCDType, new PointUpCD(1000, this->getX(), this->getY())));
		this->setState(SuperMushroomState::SUPER_MUSHROOM_DISAPPEARED);
		
	}
}

void SuperMushroom::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == SUPER_MUSHROOM_DISAPPEARED) return;

	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), D3DXVECTOR3(round(this->getX()), round(this->getY()), 0));
}

void SuperMushroom::handleHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				if (this->getState() == SUPER_MUSHROOM_MOVING_LEFT) {
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_RIGHT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT) {
					this->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_RIGHT);
				}
			}
			else if (edge == rightEdge) {
				if (this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_LEFT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_LEFT);
				}
			}
			else if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT) {
					this->setY(_component->getY() - this->getHeight());
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_LEFT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setY(_component->getY() - this->getHeight());
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_RIGHT);
				}
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == SUPER_MUSHROOM_MOVING_LEFT || this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _component->getFrame().right)
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void SuperMushroom::handleBlockCollision(Block* _block, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT) {
					this->setY(_block->getY() - this->getHeight());
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_LEFT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setY(_block->getY() - this->getHeight());
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_RIGHT);
				}
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_block->getX() <= this->getX() + this->getWidth() && this->getX() + this->getWidth() <= _block->getFrame().right)
					|| (_block->getX() <= this->getX() && this->getX() <= _block->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _block->getY()) {// - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void SuperMushroom::handleMarioCollision(Mario* _mario, float _dt)
{
	//if (this->getState() == SUPER_MUSHROOM_BEING_EARNED
	//|| this->getState() == SUPER_MUSHROOM_DISAPPEARED
	//|| _mario->getState() == SCALING_UP
	//|| _mario->getIsFlashMode()) return;

	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);

	if (get<0>(collisionResult) == true || this->isCollidingByBounds(_mario->getBounds())) {
		this->plusX(this->getVx() * get<1>(collisionResult));
		this->plusY(this->getVy() * get<1>(collisionResult));
		this->setState(SuperMushroomState::SUPER_MUSHROOM_BEING_EARNED);
		_mario->plusX(this->getVx() * get<1>(collisionResult));
		_mario->plusY(this->getVy() * get<1>(collisionResult));
		_mario->setState(MarioState::SCALING_UP);
		ScoreBoard::getInstance()->plusPoint(1000);
	}
}