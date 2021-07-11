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
		if ((*cd).first == PointUpCDType) {
			static_cast<PointUpCD*>((*cd).second)->Update(_dt);
			if (static_cast<PointUpCD*>((*cd).second)->getIsFinish()) {
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
		if ((*cd).first == PointUpCDType) {
			static_cast<PointUpCD*>((*cd).second)->Draw(_texture);
		}
	}
}

void AnimationCDPlayer::addCD(pair<CDType, AnimationCD*> cd)
{
	listCD.insert(cd);
}
