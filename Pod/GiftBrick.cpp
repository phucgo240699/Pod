#include "GiftBrick.h"

Animation* GiftBrick::getAnimation()
{
	return this->animation;
}

void GiftBrick::loadAnimation(vector<string> data)
{
	vector<RECT*>* arr = new vector<RECT*>();
	for (int i = 0; i < data.size(); ++i) {
		RECT* r = new RECT();
		vector<int> frame = Tool::splitToVectorIntegerFrom(data[i], ',');
		r->left = frame[0];
		r->top = frame[1];
		r->right = frame[0] + frame[2];
		r->bottom = frame[1] + frame[3];
		arr->push_back(r);
	}

	animation = new Animation(0, 0, 1, arr);
}

void GiftBrick::loadFrames(vector<string> data)
{
	this->frames = new vector<RECT*>();
	for (int i = 0; i < data.size(); ++i) {
		RECT* r = new RECT();
		vector<int> frame = Tool::splitToVectorIntegerFrom(data[i], ',');
		r->left = frame[0];
		r->top = frame[1];
		r->right = frame[0] + frame[2];
		r->bottom = frame[1] + frame[3];
		this->frames->push_back(r);
	}
}

void GiftBrick::Update(float _dt)
{
	if (this->animation == NULL) return;
	this->animation->Update(_dt);
}

void GiftBrick::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->animation == NULL) return;
	D3DXVECTOR3 position;
	for (int i = 0; i < this->frames->size(); ++i) {
		if (Camera::getInstance()->isColliding(this->frames->at(i))) {
			position = D3DXVECTOR3(this->frames->at(i)->left, this->frames->at(i)->right, 0);
			Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), NULL, &position);
		}
	}
}
