#include "WTurtle.h"

WTurtle::WTurtle(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

WTurtle::WTurtle(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

float WTurtle::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float WTurtle::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

void WTurtle::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setVx(stof(v[2]));
	this->setVy(stof(v[3]));

	this->leftAnchor = stof(v[4]);
	this->rightAnchor = stof(v[5]);

	this->isFlip = v[6] == "true" ? true : false;
}

void WTurtle::loadAnimation(vector<string> data, char endSeperator, char seperator)
{
	int animDelay = 0;
	vector<RECT>* arr = new vector<RECT>();
	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == endSeperator) {
			animDelay = stoi(data[i].substr(2, data[i].size()));
			continue;
		}
		arr->push_back(Tool::getRECT(data[i], seperator));
	}

	animation = new Animation(0, 0, animDelay, arr);
}

void WTurtle::Update(float _dt)
{
	this->animation->Update(_dt);

	if (this->isFlip == true) { // move to left
		if (this->getX() + (this->getVx() * _dt) <= this->leftAnchor) {
			this->setX(this->leftAnchor);
			this->isFlip = false;
			this->setVx(this->getVx() * -1);
		}
	}
	else { // move to right
		if (this->getX() + this->getWidth() + (this->getVx() * _dt) >= this->rightAnchor) {
			this->setX(this->rightAnchor - this->getWidth());
			this->isFlip = true;
			this->setVx(this->getVx() * -1);
		}

	}

	this->plusX(this->getVx() * _dt);
}

void WTurtle::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	Drawing::getInstance()->draw(_texture, animation->getCurrentFrame(), NULL, this->getPosition(), D3DXVECTOR2(0,0), isFlip);
}
