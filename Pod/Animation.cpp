#include "Animation.h"

Animation::Animation(int _id, int _indexFrame, int _animDelay)
{
	this->id = _id;
	this->currentIndexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = new vector<RECT>();
}

Animation::Animation(int _id, int _indexFrame, int _animDelay, vector<RECT>* _frames)
{
	this->id = _id;
	this->currentIndexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = _frames;
}

Animation::Animation(int _id, int _indexFrame, int _animDelay, string filePath)
{
	this->id = _id;
	this->currentIndexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = FileManager::getInstance()->getFramesFrom(filePath, ',');
}

Animation::~Animation()
{
	for (int i = 0; i < this->frames->size(); ++i) {
		delete &(this->frames->at(i));
	}

	delete this->frames;
}

int Animation::getId()
{
	return this->id;
}

int Animation::getCurrentIndexFrame()
{
	return this->currentIndexFrame;
}

int Animation::getAnimDelay()
{
	return this->animDelay;
}

int Animation::getAnimCount()
{
	return this->animCount;
}

RECT Animation::getCurrentFrame()
{
	return this->frames->at(currentIndexFrame);
}

int Animation::getTotalFrames()
{
	return this->frames->size();
}

float Animation::getCurrentFrameWidth()
{
	return this->getCurrentFrame().right - this->getCurrentFrame().left;
}

float Animation::getCurrentFrameHeight()
{
	return this->getCurrentFrame().bottom - this->getCurrentFrame().top;
}

void Animation::setCurrentIndexFrame(int _indexFrame)
{
	this->currentIndexFrame = _indexFrame;
}

void Animation::setAnimCount(int _animCount)
{
	this->animCount = _animCount;
}

void Animation::Update(float _dt)
{
	if (this->getAnimCount() == this->getAnimDelay()) {
		this->setAnimCount(0);
		if (this->getTotalFrames() - 1 == 0) {
			return;
		}
		
		this->setCurrentIndexFrame(this->getCurrentIndexFrame() + 1);

		if (this->getCurrentIndexFrame() > this->getTotalFrames() - 1) {
			this->setCurrentIndexFrame(0);
		}
	}
	else {
		this->setAnimCount(this->getAnimCount() + 1);
	}
}

void Animation::Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3* _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{
	Drawing::getInstance()->draw(_texture, this->getCurrentFrame(), NULL, _position, _translation, _isFlip, _color);
}

void Animation::Draw(LPDIRECT3DTEXTURE9 _texture, RECT _srcRect, D3DXVECTOR3* _position)
{
	Drawing::getInstance()->draw(_texture, _srcRect, _position);
}
