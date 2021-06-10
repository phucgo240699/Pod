#include "StaticAnim.h"

void StaticAnim::loadAnimation(vector<string> data, char endSeperator, char seperator)
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

void StaticAnim::loadFrames(vector<string> data, char seperator)
{
	this->frames = Tool::getRECTs(data, seperator);
}

Animation* StaticAnim::getAnimation()
{
	return this->animation;
}

void StaticAnim::Update(float _dt)
{
	animation->Update(_dt);
}

void StaticAnim::Draw(LPDIRECT3DTEXTURE9 _texture)
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
