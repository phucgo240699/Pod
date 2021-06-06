#include "Grass.h"

void Grass::loadAnimation(vector<string> data, char endSeperator, char seperator)
{
	int animDelay;
	vector<RECT>* arr = new vector<RECT>();
	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == endSeperator) {
			animDelay = stoi(data[i].substr(2, 1));
			continue;
		}
		arr->push_back(Tool::getRECT(data[i], seperator));
	}

	animation = new Animation(0, 0, animDelay, arr);
}

void Grass::loadFrames(vector<string> data, char seperator)
{
	this->frames = Tool::getRECTs(data, seperator);
}

Animation* Grass::getAnimation()
{
	return this->animation;
}

void Grass::Update(float _dt)
{
	animation->Update(_dt);
}

void Grass::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	if (this->animation == NULL) return;

	D3DXVECTOR3 position;

	for (int i = 0; i < this->frames->size(); ++i) {
		if (Camera::getInstance()->isColliding(this->frames->at(i))) {
			position = D3DXVECTOR3(this->frames->at(i).left - Camera::getInstance()->getX(), this->frames->at(i).top - Camera::getInstance()->getY(), 0);
			Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), NULL, &position);
		}
	}
}
