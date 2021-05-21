#include "Component.h"

Component::Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = new D3DXVECTOR3(_x, _y, 0);
	this->vx = _vx;
	this->vy = _vy;
	this->currentVx = _vx;
	this->currentVy = _vy;
	this->limitX = _limitX;
	this->limitY = _limitY;
}

Component::Component(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = _position;
	this->vx = _vx;
	this->vy = _vy;
	this->currentVx = _vx;
	this->currentVy = _vy;
	this->limitX = _limitX;
	this->limitY = _limitY;
}

Component::~Component()
{
	delete position;
}

D3DXVECTOR3* Component::getPosition()
{
	return this->position;
}

float Component::getX()
{
	return this->position->x;
}

float Component::getY()
{
	return this->position->y;
}

float Component::getVx()
{
	return this->vx;
}

float Component::getVy()
{
	return this->vy;
}

float Component::getCurrentVx()
{
	return this->currentVx;
}

float Component::getCurrentVy()
{
	return this->currentVy;
}

float Component::getLimitX()
{
	return this->limitX;
}

float Component::getLimitY()
{
	return this->limitY;
}

void Component::setPosition(D3DXVECTOR3* _position)
{
	this->position = _position;
}

void Component::setX(float _x)
{
	this->position->x = _x;
}

void Component::setY(float _y)
{
	this->position->y = _y;
}

void Component::setVx(float _vx)
{
	this->vx = _vx;
}

void Component::setVy(float _vy)
{
	this->vy = _vy;
}

void Component::setCurrentVx(float _currentVx)
{
	this->currentVx = _currentVx;
}

void Component::setCurrentVy(float _currentVy)
{
	this->currentVy = _currentVy;
}

void Component::setLimitX(float _limitX)
{
	this->limitX = _limitX;
}

void Component::setLimitY(float _limitY)
{
	this->limitY = _limitY;
}

void Component::plusX(float _x)
{
	this->position->x += _x;
}

void Component::plusY(float _y)
{
	this->position->y += _y;
}

void Component::Update(float _dt)
{
}

void Component::Draw()
{
}

RECT* Component::getBounds()
{
	return nullptr;
}

void Component::onKeyUp()
{
}

void Component::onKeyDown(KeyType _keyType)
{
}

bool Component::isColliding(RECT* other)
{
	float left = other->left - this->getBounds()->right;
	float top = other->bottom - this->getBounds()->top;
	float right = other->right - this->getBounds()->left;
	float bottom = other->top - this->getBounds()->bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

RECT Component::getSweptBroadphaseRect()
{
	RECT r;
	r.left = this->getCurrentVx() > 0 ? this->getX() : this->getX() + this->getCurrentVx();
	r.top = this->getCurrentVy() > 0 ? this->getY() : this->getY() + this->getCurrentVy();
	r.right = this->getCurrentVx() > 0 ? this->getBounds()->right + this->getCurrentVx() : this->getBounds()->right;
	r.bottom = this->getCurrentVy() > 0 ? this->getBounds()->bottom + this->getCurrentVy() : this->getBounds()->bottom;

	return r;
}

tuple<bool, float, vector<CollisionEdge>> Component::sweptAABB(Component* other, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> result = tuple<bool, float, vector<CollisionEdge>>();
	float dxEntry, dxExit;
	float dyEntry, dyExit;
	float txEntry, txExit;
	float tyEntry, tyExit;

	// Distance
	if (this->getCurrentVx() > 0.0f)
	{
		dxEntry = other->getX() - this->getBounds()->right;
		dxExit = other->getBounds()->right - this->getX();
	}
	else
	{
		dxEntry = other->getBounds()->right - this->getX();
		dxExit = other->getX() - this->getBounds()->right;
	}
	if (this->getCurrentVy() > 0.0f)
	{
		dyEntry = other->getY() - this->getBounds()->bottom;
		dyExit = other->getBounds()->bottom - this->getY();
	}
	else
	{
		dyEntry = other->getBounds()->bottom - this->getY();
		dyExit = other->getY() - this->getBounds()->bottom;
	}


	// Time
	if (this->getCurrentVx() == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / this->getCurrentVx();
		txExit = dxExit / this->getCurrentVx();
	}
	if (this->getCurrentVy() == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / this->getCurrentVy();
		tyExit = dyExit / this->getCurrentVy();
	}
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);


	// Result
	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > _dt || tyEntry > _dt)
	{
		get<0>(result) = false;
	}
	else // if there was a collision 
	{
		get<0>(result) = true;
		get<1>(result) = entryTime;

		// calculate collided surface
		if (txEntry > tyEntry)
		{
			if (dxEntry > 0.0f)
			{
				get<2>(result).push_back(CollisionEdge::rightEdge);
			}
			else
			{
				get<2>(result).push_back(CollisionEdge::leftEdge);
			}
		}
		else
		{
			if (dyEntry > 0.0f)
			{
				get<2>(result).push_back(CollisionEdge::topEdge);
			}
			else
			{
				get<2>(result).push_back(CollisionEdge::bottomEdge);
			}
		} // return the time of collisionreturn entryTime; 
	}

	return result;
}
