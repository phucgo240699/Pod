#include "Goomba.h"

Goomba::Goomba(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

Goomba::Goomba(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Enemy(_position, _vx, _vy, _limitX, _limitY)
{
}

void Goomba::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(0.5);
	this->setVy(0);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setId(v[4]);
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
			this->animation = new Animation(AnimationBundle::getInstance()->getTrampledGoomba());
		}
		break;
	default:
		break;
	}
	this->state = _state;
}

void Goomba::Update(float _dt)
{
	this->plusX(this->getVx() * _dt);
	this->plusY(this->getVy() * _dt);

	// update which cell in grid that it's belongs to
	Grid::getInstance()->updateCellOf(this);

	this->animation->Update(_dt);
}

void Goomba::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
}
