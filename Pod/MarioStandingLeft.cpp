#include "MarioStandingLeft.h"

MarioStandingLeft::MarioStandingLeft(int _id, int _indexFrame, int _animDelay) : Animation(_id, _indexFrame, _animDelay)
{
}

MarioStandingLeft::MarioStandingLeft(int _id, int _indexFrame, int _animDelay, vector<RECT*>* _frames) : Animation(_id, _indexFrame, _animDelay, _frames)
{
}

MarioStandingLeft::MarioStandingLeft(int _id, int _indexFrame, int _animDelay, string filePath) : Animation(_id, _indexFrame, _animDelay, filePath)
{
}

void MarioStandingLeft::Update(float _dt)
{
	if (this->getAnimCount() == this->getAnimDelay()) {
		this->setAnimCount(0);
		int currentIndexFrame = this->getIndexFrame();
		int lastIndexFrame = this->getTotalFrames() - 1;
		if (currentIndexFrame > lastIndexFrame || lastIndexFrame == 0) {
			this->setIndexFrame(0);
		}
		else {
			this->setIndexFrame(currentIndexFrame + 1);
		}
	}
	else {
		this->setAnimCount(this->getAnimCount() + 1);
	}
}

void MarioStandingLeft::Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3* _position, D3DCOLOR _color)
{
	Drawing::getInstance()->draw(_texture, this->getCurrentFrame(), NULL, _position, _color);
}
