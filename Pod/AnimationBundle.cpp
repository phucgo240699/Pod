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
	vector<pair<RECT, RECT>>* frames = new vector<pair<RECT, RECT>>();

	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == '>') {
			vector<string> v = Tool::splitToVectorStringFrom(data[i], ' ');
			id = stoi(v[1]);
			startIndexFrame = stoi(v[2]);
			animDelay = stoi(v[3]);

			this->animations->push_back(Animation(id, startIndexFrame, animDelay, frames));
			frames = new vector<pair<RECT, RECT>>();

			continue;
		}
		
		vector<float> v = Tool::splitToVectorFloatFrom(data[i], seperator);
		if (v.size() == 8) {
			RECT rectBounds = RECT();
			rectBounds.left = v[0];
			rectBounds.top = v[1];
			rectBounds.right = rectBounds.left + v[2];
			rectBounds.bottom = rectBounds.top + v[3];

			RECT rectFrame = RECT();
			rectFrame.left = v[4];
			rectFrame.top = v[5];
			rectFrame.right = rectFrame.left + v[6];
			rectFrame.bottom = rectFrame.top + v[7];

			frames->push_back(pair<RECT, RECT>(rectBounds, rectFrame));
		}
		else {
			RECT rectFrame = RECT();
			rectFrame.left = v[0];
			rectFrame.top = v[1];
			rectFrame.right = rectFrame.left + v[2];
			rectFrame.bottom = rectFrame.top + v[3];

			frames->push_back(pair<RECT, RECT>(rectFrame, rectFrame));
		}
	}
}

Animation AnimationBundle::getWMario()
{
	return this->animations->at(0);
}

Animation AnimationBundle::getGrasses()
{
	return this->animations->at(1);
}

Animation AnimationBundle::getHelpLabel()
{
	return this->animations->at(2);
}

Animation AnimationBundle::getWTurtle()
{
	return this->animations->at(3);
}

//Animation AnimationBundle::getAnimationAt(int index)
//{
//	return this->animations->at(index);
//}

Animation AnimationBundle::getMarioStanding()
{
	return this->animations->at(0);
}

Animation AnimationBundle::getMarioWalking()
{
	return this->animations->at(1);
}

Animation AnimationBundle::getMarioDropping()
{
	return this->animations->at(2);
}

Animation AnimationBundle::getMarioJumping()
{
	return this->animations->at(2);
}

Animation AnimationBundle::getMarioDie()
{
	return this->animations->at(3);
}

Animation AnimationBundle::getGoldenBrick()
{
	return this->animations->at(4);
}

Animation AnimationBundle::getFullGiftBrick()
{
	return this->animations->at(5);
}

Animation AnimationBundle::getEmptyGiftBrick()
{
	return this->animations->at(6);
}

Animation AnimationBundle::getCoin()
{
	return this->animations->at(7);
}

Animation AnimationBundle::get100Points()
{
	return this->animations->at(8);
}

Animation AnimationBundle::getGoombaMoving()
{
	return this->animations->at(9);
}

Animation AnimationBundle::getTrampledGoomba()
{
	return this->animations->at(10);
}

Animation AnimationBundle::getGreenPipe3Floor()
{
	return this->animations->at(11);
}

Animation AnimationBundle::getGreenPipe2Floor()
{
	return this->animations->at(12);
}

Animation AnimationBundle::getSuperMushroom()
{
	return this->animations->at(13);
}

Animation AnimationBundle::getSuperMarioStanding()
{
	return this->animations->at(14);
}

Animation AnimationBundle::getSuperMarioWalking()
{
	return this->animations->at(15);
}

Animation AnimationBundle::getSuperMarioDropping()
{
	return this->animations->at(16);
}

Animation AnimationBundle::getSuperMarioJumping()
{
	return this->animations->at(16);
}
