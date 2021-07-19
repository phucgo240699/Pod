#include "AnimationCDPlayer.h"
AnimationCDPlayer* AnimationCDPlayer::instance;
AnimationCDPlayer* AnimationCDPlayer::getInstance()
{
	if (instance == NULL) {
		instance = new AnimationCDPlayer();
	}
	return instance;
}

void AnimationCDPlayer::Update(float _dt)
{

	//for (auto cd = listCD.begin(); cd != listCD.end();) {
	//	// Check is CD finish
	//	if ((*cd).second->getIsFinish()) {
	//		this->listCD.erase(cd++);
	//	}
	//	else {
	//		++cd;
	//	}
	//}

	for (auto cd = listCD.begin(); cd != listCD.end();) {
		//if ((*cd).second->getIsFinish() == false) {
			if ((*cd).second->getIsFinish()) {
				this->listCD.erase(cd++);
			}
			else {
				(*cd).second->Update(_dt);
				++cd;
			}
			// Check is CD finish
		//}
	}

}

void AnimationCDPlayer::Draw(LPDIRECT3DTEXTURE9 _texture)
{

	for (auto cd = listCD.begin(); cd != listCD.end(); cd++) {
		(*cd).second->Draw(_texture);
	}
}

void AnimationCDPlayer::addCD(pair<CDType, AnimationCD*> cd)
{
	listCD.insert(cd);
}
