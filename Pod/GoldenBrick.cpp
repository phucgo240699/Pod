#include "GoldenBrick.h"

GoldenBrick::GoldenBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
}

GoldenBrick::GoldenBrick(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, int _id) : Component(_position, _vx, _vy, _limitX, _limitY)
{
}

void GoldenBrick::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setWidth(v[2]);
	this->setHeight(v[3]);
	this->setId(v[4]);
}

void GoldenBrick::loadAnimation(vector<string> data, char endSeperator, char seperator)
{
	int animDelay = 0;
	vector<RECT>* arr = new vector<RECT>();
	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == endSeperator) {
			animDelay = stoi(data[i].substr(2, 1));
			continue;
		}
		RECT r = RECT();
		vector<int> frame = Tool::splitToVectorIntegerFrom(data[i], seperator);
		r.left = frame[0];
		r.top = frame[1];
		r.right = frame[0] + frame[2];
		r.bottom = frame[1] + frame[3];
		arr->push_back(r);
	}

	animation = new Animation(0, 0, animDelay, arr);
}

void GoldenBrick::Update(float _dt)
{
	animation->Update(_dt);
}

void GoldenBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	D3DXVECTOR3 position = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), &position);
}
