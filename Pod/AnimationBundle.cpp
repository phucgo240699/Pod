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
