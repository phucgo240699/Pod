#include "Goomba.h"
#include "Mario.h"

Goomba::Goomba(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

Goomba::Goomba(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_position, _vx, _vy, _limitX, _limitY)
{
}

void Goomba::loadInfo(string line, char seperator)
{
	vector<float> v = Tool::splitToVectorFloatFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setVx(v[4]);
	this->setVy(v[5]);
	this->setId(v[6]);

	this->pointY = this->getY() - 16;
	this->endPointJumpUp = this->getY() - 48;
	this->originVx = abs(this->getVx());
	this->originVy = abs(this->getVy());
}

GoombaState Goomba::getState()
{
	return this->state;
}

bool Goomba::getIsStandOnSurface()
{
	return this->isStandOnSurface;
}

void Goomba::setState(GoombaState _state)
{
	switch (_state)
	{
	case GOOMBA_STANDING:
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
			this->setVx(0);
			this->setVy(0);
		}
		break;

	case GOOMBA_MOVING_LEFT:
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(-originVx);
		this->setVy(0);
		break;

	case GOOMBA_MOVING_RIGHT:
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(originVx);
		this->setVy(0);
		break;

	case GOOMBA_DROPPING_LEFT:
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(-originVx);
		this->setVy(originVy);
		break;

	case GOOMBA_DROPPING_RIGHT:
		if (this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		this->setVx(originVx);
		this->setVy(originVy);
		break;

	case TRAMPLED_GOOMBA:
		if (this->getState() == GOOMBA_MOVING_LEFT || GOOMBA_MOVING_RIGHT) {
			this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());
			this->pointAnimation = new Animation(AnimationBundle::getInstance()->get100Points());
			this->setVx(0);
			this->setVy(0);
		}
		break;

	case DEAD_GOOMBA:
		if (this->getState() == TRAMPLED_GOOMBA) {
			this->animation = NULL;
			this->pointAnimation = NULL;
			this->setVx(0);
			this->setVy(0);
		}
		break;
	default:
		break;
	}
	this->state = _state;
}

void Goomba::setIsStandOnSurface(bool _isStandOnSurface)
{
	this->isStandOnSurface = _isStandOnSurface;
}

void Goomba::Update(float _dt)
{
	if (this->getState() == DEAD_GOOMBA || this->getState() == GOOMBA_STANDING) return;

	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}
	
	if (this->getState() == GOOMBA_MOVING_LEFT || this->getState() == GOOMBA_MOVING_RIGHT) {
		if (this->getX() + this->getVx() * _dt >= 0
		&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()) {
			this->plusX(this->getVx() * _dt);
		}
	}
	else if (this->getState() == GOOMBA_DROPPING_LEFT || this->getState() == GOOMBA_DROPPING_RIGHT) {
		if (this->getY() + this->getVy() * _dt >= 0
			&& this->getY() + this->getHeight() + this->getVy() * _dt <= Camera::getInstance()->getLimitY()) {
			this->plusX(this->getVx() * _dt);
			this->plusY(this->getVy() * _dt);
		}
	}
	else if (this->getState() == TRAMPLED_GOOMBA && this->pointAnimation != NULL) {
		this->pointAnimation->Update(_dt);
		if (this->pointY - 2 >= this->endPointJumpUp) {
			this->pointY -= 2;
		}
		else {
			this->pointY = this->endPointJumpUp;
			this->setState(GoombaState::DEAD_GOOMBA);
		}
	}

	if (this->animation != NULL) {
		this->animation->Update(_dt);
	}
}

void Goomba::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->getState() == DEAD_GOOMBA) return;
	if (this->getState() == TRAMPLED_GOOMBA && this->pointAnimation != NULL) {
		Drawing::getInstance()->draw(_texture, this->pointAnimation->getCurrentFrame(), D3DXVECTOR3(this->getX(), this->pointY, 0));
		if (this->pointY <= this->endPointJumpUp && this->animation != NULL) {
			this->animation = NULL;
		}
	}
	if (this->animation != NULL) {
		Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
	}
}

void Goomba::handleHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_component, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				if (this->getState() == GOOMBA_MOVING_LEFT) {
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
				else if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
				}
			}
			else if (edge == rightEdge) {
				if (this->getState() == GOOMBA_MOVING_RIGHT) {
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
				}
			}
			else if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == GOOMBA_DROPPING_LEFT) {
					this->setY(_component->getY() - this->getHeight());
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (this->getState() == GOOMBA_DROPPING_RIGHT) {
					this->setY(_component->getY() - this->getHeight());
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == GOOMBA_MOVING_LEFT || this->getState() == GOOMBA_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getFrame().right && this->getFrame().right <= _component->getFrame().right)
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getY() + this->getHeight() == _component->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}

		if (this->getIsStandOnSurface() == false && this->getState() == GOOMBA_MOVING_LEFT) {
			this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
			return;
		}
		else if (this->getIsStandOnSurface() == false && this->getState() == GOOMBA_MOVING_RIGHT) {
			this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
			return;
		}
	}
}

void Goomba::handleBlockCollision(Component* _block, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_block, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == bottomEdge) {
				this->setIsStandOnSurface(true);
				if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT) {
					this->setY(_block->getY() - this->getHeight());
					this->setState(GoombaState::GOOMBA_MOVING_LEFT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setY(_block->getY() - this->getHeight());
					this->setState(GoombaState::GOOMBA_MOVING_RIGHT);
				}
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (this->getState() == WALKING || this->getState() == STANDING) {
			if (this->getIsStandOnSurface() == false) {
				if ((_block->getX() <= this->getFrame().right && this->getFrame().right <= _block->getFrame().right)
					|| (_block->getX() <= this->getX() && this->getX() <= _block->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom == _block->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}

		if (this->getIsStandOnSurface() == false && this->getState() == GOOMBA_MOVING_LEFT) {
			this->setState(GoombaState::GOOMBA_DROPPING_LEFT);
			return;
		}
		else if (this->getIsStandOnSurface() == false && this->getState() == GOOMBA_MOVING_RIGHT) {
			this->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
			return;
		}
	}
}

void Goomba::handleMarioCollision(Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByBounds(_mario, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				this->setState(GoombaState::GOOMBA_STANDING);
			}
			else if (edge == rightEdge) {
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * this->getVx());
				this->setState(GoombaState::GOOMBA_STANDING);
			}
		}
	}
}