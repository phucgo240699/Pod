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
	for (auto cd = listCD.begin(); cd != listCD.end();) {
		(*cd).second->Update(_dt);

		//// Check is CD finish
		//if ((*cd).second->getIsFinish()) {
		//	this->listCD.erase(cd++);
		//}
		//else {
		//	++cd;
		//}
		auto currentCd = cd++;
		if ((*currentCd).second->getIsFinish()) {
			listCD.erase(currentCd);
		}
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
