#include "Animation.h"

Animation::Animation(int _id, int _indexFrame, int _animDelay)
{
	this->id = _id;
	this->indexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = new vector<RECT*>();
}

Animation::Animation(int _id, int _indexFrame, int _animDelay, vector<RECT*>* _frames)
{
	this->id = _id;
	this->indexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = _frames;
}

Animation::Animation(int _id, int _indexFrame, int _animDelay, string filePath)
{
	this->id = _id;
	this->indexFrame = _indexFrame;
	this->animDelay = _animDelay;
	this->animCount = 0;
	this->frames = FileManager::getInstance()->getFramesFrom(filePath, ',');
}

Animation::~Animation()
{
	for (int i = 0; i < this->frames->size(); ++i) {
		delete (this->frames->at(i));
	}

	delete this->frames;
}

int Animation::getId()
{
	return this->id;
}

int Animation::getIndexFrame()
{
	return this->indexFrame;
}

int Animation::getAnimDelay()
{
	return this->animDelay;
}

int Animation::getAnimCount()
{
	return this->animCount;
}

RECT* Animation::getCurrentFrame()
{
	return this->frames->at(indexFrame);
}

int Animation::getTotalFrames()
{
	return this->frames->size();
}

float Animation::getCurrentFrameWidth()
{
	return this->getCurrentFrame()->right - this->getCurrentFrame()->left;
}

float Animation::getCurrentFrameHeight()
{
	return this->getCurrentFrame()->bottom - this->getCurrentFrame()->top;
}

void Animation::setIndexFrame(int _indexFrame)
{
	this->indexFrame = _indexFrame;
}

void Animation::setAnimCount(int _animCount)
{
	this->animCount = _animCount;
}

void Animation::Update(float _dt)
{
}

void Animation::Draw(LPDIRECT3DTEXTURE9 _texture, D3DXVECTOR3* _position, D3DCOLOR _color)
{
}
