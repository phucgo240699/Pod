#include "AnimationBundle.h"

AnimationBundle* AnimationBundle::instance;

AnimationBundle* AnimationBundle::getInstance()
{
	if (AnimationBundle::instance == nullptr) {
		instance = new AnimationBundle();
	}
	return instance;
}

void AnimationBundle::loadAnimations(vector<string> data, char endSperator, char seperator)
{
	int id = 0;
	int startIndexFrame = 0;
	int animDelay = 0;
	this->animations = new vector<Animation>();
	vector<RECT>* frames = new vector<RECT>();

	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == '>') {
			vector<string> v = Tool::splitToVectorStringFrom(data[i], ' ');
			id = stoi(v[1]);
			startIndexFrame = stoi(v[2]);
			animDelay = stoi(v[3]);

			this->animations->push_back(Animation(id, startIndexFrame, animDelay, frames));
			frames = new vector<RECT>();

			continue;
		}
		frames->push_back(Tool::getRECT(data[i], seperator));
	}
}

Animation AnimationBundle::getAnimationAt(int index)
{
	return this->animations->at(index);
}

Animation AnimationBundle::getFullGiftBrick()
{
	return this->animations->at(0);
}

Animation AnimationBundle::getEmptyGiftBrick()
{
	return this->animations->at(1);
}

Animation AnimationBundle::getCoin()
{
	return this->animations->at(2);
}

Animation AnimationBundle::get100Points()
{
	return this->animations->at(3);
}

Animation AnimationBundle::getGoombaMoving()
{
	return this->animations->at(4);
}

Animation AnimationBundle::getTrampledGoomba()
{
	return this->animations->at(5);
}

Animation AnimationBundle::getGreenPipe3Floor()
{
	return this->animations->at(6);
}

Animation AnimationBundle::getGreenPipe2Floor()
{
	return this->animations->at(7);
}
