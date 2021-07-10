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
		if ((*cd).first == PointCDType) {
			static_cast<PointCD*>((*cd).second)->Update(_dt);
			if (static_cast<PointCD*>((*cd).second)->getIsFinish()) {
				this->listCD.erase(cd++);
			}
			else {
				++cd;
			}
		}
	}
}

void AnimationCDPlayer::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	for (auto cd = listCD.begin(); cd != listCD.end(); cd++) {
		if ((*cd).first == PointCDType) {
			static_cast<PointCD*>((*cd).second)->Draw(_texture);
		}
	}
}

void AnimationCDPlayer::addCD(pair<CDType, AnimationCD*> cd)
{
	listCD.insert(cd);
}
