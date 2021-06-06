#include "Component.h"

Component::Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = new D3DXVECTOR3(_x, _y, 0);
	this->vx = round(_vx);
	this->vy = round(_vy);
	/*this->currentVx = _vx;
	this->currentVy = _vy;*/
	this->limitX = _limitX;
	this->limitY = _limitY;
}

Component::Component(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY)
{
	this->position = _position;
	this->vx = round(_vx);
	this->vy = round(_vy);
	/*this->currentVx = _vx;
	this->currentVy = _vy;*/
	this->limitX = _limitX;
	this->limitY = _limitY;
}

//Component::~Component()
//{
//	delete position;
//}

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

//float Component::getVx()
//{
//	return this->vx;
//}
//
//float Component::getVy()
//{
//	return this->vy;
//}

float Component::getVx()
{
	return this->vx;
}

float Component::getVy()
{
	return this->vy;
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

//void Component::setVx(float _vx)
//{
//	this->vx = _vx;
//}
//
//void Component::setVy(float _vy)
//{
//	this->vy = _vy;
//}

void Component::setVx(float _vx)
{
	this->vx = _vx;
}

void Component::setVy(float _vy)
{
	this->vy = _vy;
}

void Component::setLimitX(float _limitX)
{
	this->limitX = round(_limitX);
}

void Component::setLimitY(float _limitY)
{
	this->limitY = round(_limitY);
}

void Component::plusX(float _x)
{
	this->position->x += round(_x);
}

void Component::plusY(float _y)
{
	this->position->y += round(_y);
}

void Component::plusVx(float _vx)
{
	this->vx += _vx;
}

void Component::plusVy(float _vy)
{
	this->vy += _vy;
}

void Component::Update(float _dt)
{
}

void Component::Draw()
{
}

RECT Component::getBounds()
{
	RECT r = RECT();
	r.top = this->getY();
	r.bottom = r.top + this->getHeight();
	r.left = this->getX();
	r.right = r.left + this->getWidth();

	return r;
}

float Component::getWidth()
{
	return this->width;
}

float Component::getHeight()
{
	return this->height;
}

void Component::setWidth(float _width)
{
	this->width = _width;
}

void Component::setHeight(float _height)
{
	this->height = _height;
}

void Component::onKeyUp()
{
}

void Component::onKeyUp(vector<KeyType> _keyTypes)
{
}

void Component::onKeyDown(vector<KeyType> _keyTypes)
{
}

bool Component::isColliding(RECT other)
{
	float left = other.left - this->getBounds().right;
	float top = other.bottom - this->getBounds().top;
	float right = other.right - this->getBounds().left;
	float bottom = other.top - this->getBounds().bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

bool Component::isColliding(RECT object, RECT other)
{
	float left = other.left - object.right;
	float top = other.bottom - object.top;
	float right = other.right - object.left;
	float bottom = other.top - object.bottom;
	
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

RECT Component::getSweptBroadphaseRect()
{
	RECT r = RECT();

	r.left = this->getVx() > 0 ? this->getX() : this->getX() + this->getVx();
	r.top = this->getVy() > 0 ? this->getY() : this->getY() + this->getVy();
	r.right = this->getVx() > 0 ? this->getBounds().right + this->getVx() : this->getBounds().right;
	r.bottom = this->getVy() > 0 ? this->getBounds().bottom + this->getVy() : this->getBounds().bottom;

	return r;
}

tuple<bool, float, vector<CollisionEdge>> Component::sweptAABB(Component* other, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> result = tuple<bool, float, vector<CollisionEdge>>();
	float dxEntry, dxExit;
	float dyEntry, dyExit;
	float txEntry, txExit;
	float tyEntry, tyExit;

	// Quick result
	if (this->isColliding(this->getSweptBroadphaseRect(), other->getBounds()) == false) { // No Collide
		get<0>(result) = false;
		return result;
	}

	// Distance
	if (this->getVx() > 0.0f)
	{
		dxEntry = other->getX() - this->getBounds().right;
		dxExit = other->getBounds().right - this->getX();
	}
	else
	{
		dxEntry = other->getBounds().right - this->getX();
		dxExit = other->getX() - this->getBounds().right;
	}
	if (this->getVy() > 0.0f)
	{
		dyEntry = other->getY() - this->getBounds().bottom;
		dyExit = other->getBounds().bottom - this->getY();
	}
	else
	{
		dyEntry = other->getBounds().bottom - this->getY();
		dyExit = other->getY() - this->getBounds().bottom;
	}


	// Time
	if (this->getVx() == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / this->getVx();
		txExit = dxExit / this->getVx();
	}
	if (this->getVy() == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / this->getVy();
		tyExit = dyExit / this->getVy();
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
