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
}

GoombaState Goomba::getState()
{
	return this->state;
}

void Goomba::setState(GoombaState _state)
{
	switch (_state)
	{
	case GOOMBA_MOVING:
		if (this->getState() != GOOMBA_MOVING || this->animation == NULL) {
			this->animation = new Animation(AnimationBundle::getInstance()->getGoombaMoving());
		}
		break;
	case TRAMPLED_GOOMBA:
		if (this->getState() == GOOMBA_MOVING) {
			this->setVx(0);
			this->setVy(0);
			this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());
			this->pointAnimation = new Animation(AnimationBundle::getInstance()->get100Points());
		}
		break;

	case DEAD_GOOMBA:
		if (this->getState() == TRAMPLED_GOOMBA) {
			this->setVx(0);
			this->setVy(0);
			this->animation = NULL;
			this->pointAnimation = NULL;
		}
	case GOOMBA_STANDING:
		this->setVx(0);
		this->setVy(0);
		break;
	default:
		break;
	}
	this->state = _state;
}

void Goomba::Update(float _dt)
{
	if (this->getState() == DEAD_GOOMBA) return;
	if (this->getX() + this->getVx() * _dt >= 0
		&& this->getX() + this->getWidth() + this->getVx() * _dt <= Camera::getInstance()->getLimitX()
		&& this->getY() + this->getVy() * _dt >= 0
		&& this->getY() + this->getHeight() + this->getVy() * _dt <= Camera::getInstance()->getLimitY()) {
		this->plusX(this->getVx() * _dt);
		this->plusY(this->getVy() * _dt);

		// update which cell in grid that it's belongs to
		Grid::getInstance()->updateCellOf(this);
	}

	if (this->animation != NULL) {
		this->animation->Update(_dt);
	}
	if (this->getState() == TRAMPLED_GOOMBA && this->pointAnimation != NULL) {
		this->pointAnimation->Update(_dt);
		if (this->pointY - 2 >= this->endPointJumpUp) {
			this->pointY -= 2;
		}
		else {
			this->pointY = this->endPointJumpUp;
			this->setState(GoombaState::DEAD_GOOMBA);
		}
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

void Goomba::handleGroundCollision(Component* _ground, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABB(_ground, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				this->setVx(abs(this->getVx()));
			}
			else if (edge == rightEdge) {
				this->setVx(abs(this->getVx()) * -1);
			}
		}
	}
}

void Goomba::handleMarioCollision(Mario* _mario, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> collisionResult = this->sweptAABB(_mario, _dt);
	if (get<0>(collisionResult) == true) {
		for (int j = 0; j < get<2>(collisionResult).size(); ++j) {
			CollisionEdge edge = get<2>(collisionResult)[j];
			if (edge == leftEdge) {
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * _dt);
				this->setState(GoombaState::GOOMBA_STANDING);
			}
			else if (edge == rightEdge) {
				_mario->setState(MarioState::DIE);
				this->plusX(get<1>(collisionResult) * _dt);
				this->setState(GoombaState::GOOMBA_STANDING);
			}
		}
	}
}
