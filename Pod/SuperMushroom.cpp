#include "SuperMushroom.h"
#include "Block.h"

//SuperMushroom::SuperMushroom(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
//{
//}

SuperMushroom::SuperMushroom(float _x, float _y, float _width, float _height, float _vx, float _vy, int _id, int _endGrowupPoint) : Component(_x, _y, _vx, _vy, 0, 0)
{
	Component::Component(_x, _y, _vx, _vy, 0, 0);
	this->setId(_id);
	this->setWidth(_width);
	this->setHeight(_height);
	this->endGrowupPoint = _endGrowupPoint;
}

//SuperMushroom::SuperMushroom(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
//{
//}

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
	if (animation == NULL) {
		this->animation = new Animation(AnimationBundle::getInstance()->getSuperMushroom());
	}
	switch (_state)
	{
	case SUPER_MUSHROOM_GROWING_UP:
		this->setVx(0);
		this->setVy(-1 * abs(this->getVy()));
		break;
	case SUPER_MUSHROOM_MOVING_LEFT:
		this->setVx(-1 * abs(this->getVy()));
		break;
	case SUPER_MUSHROOM_MOVING_RIGHT:
		this->setVx(abs(this->getVy()));
		break;
	case SUPER_MUSHROOM_DROPPING_LEFT:
		this->setVx(-1 * abs(this->getVy()));
		this->setVy(abs(this->getVy()) * 0.5);
		break;
	case SUPER_MUSHROOM_DROPPING_RIGHT:
		this->setVx(abs(this->getVy()));
		this->setVy(abs(this->getVy()) * 0.5);
		break;
	default:
		break;
	}
	this->state = _state;
}

void SuperMushroom::setIsStandOnSurface(bool _isStandOnSurface)
{
	this->isStandOnSurface = _isStandOnSurface;
}

void SuperMushroom::loadInfo(int _x, int _y, int _width, int _height, int _vx, int _vy, int _id)
{
	this->setX(_x);
	this->setY(_y);
	this->setWidth(_width);
	this->setHeight(_height);
	this->setVx(_vx);
	this->setVy(_vy);
	this->setId(_id);

	// Random number
	srand(time(NULL));

	int randomNumber = rand() % 2 + 1;
	this->moveLeftFirst = randomNumber == 1 ? true : false;
}

void SuperMushroom::Update(float _dt)
{
	if (this->getIsStandOnSurface() == true) {
		this->setIsStandOnSurface(false);
	}

	if (this->getState() == SUPER_MUSHROOM_GROWING_UP) {
		if (this->getY() + (this->getVy() * _dt) < this->endGrowupPoint) {
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
	}
	else if (this->getState() == SUPER_MUSHROOM_MOVING_LEFT || this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
		this->plusX(this->getVx() * _dt);
	}
	else if (this->getState() == SUPER_MUSHROOM_DROPPING_LEFT || this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
		this->plusX(this->getVx() * _dt);
		this->plusY(this->getVy() * _dt);
	}

	// update which cell in grid that it's belongs to
	Grid::getInstance()->updateCellOf(this);
}

void SuperMushroom::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}

void SuperMushroom::handleHardComponentCollision(Component* _component, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABBByFrame(_component, _dt);
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
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_LEFT);
				}
				else if (this->getState() == SUPER_MUSHROOM_DROPPING_RIGHT) {
					this->setState(SuperMushroomState::SUPER_MUSHROOM_MOVING_RIGHT);
				}
			}
		}
	}
	else {
		// if supermushroom walk out of ground's top surface, it will drop
		if (this->getState() == SUPER_MUSHROOM_MOVING_LEFT || this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
			if (this->getIsStandOnSurface() == false) {
				if ((_component->getX() <= this->getFrame().right && this->getFrame().right <= _component->getFrame().right)
					|| (_component->getX() <= this->getX() && this->getX() <= _component->getFrame().right)) { // this is check which ground that mario is standing on
					if (this->getFrame().bottom <= _component->getY()) {
						this->setIsStandOnSurface(true);
					}
				}
			}
		}

		if (this->getIsStandOnSurface() == false && this->getState() == SUPER_MUSHROOM_MOVING_LEFT) {
			this->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_LEFT);
			return;
		}
		else if (this->getIsStandOnSurface() == false && this->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
			this->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_RIGHT);
			return;
		}
	}
}