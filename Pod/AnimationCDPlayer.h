#pragma once
#include "CDType.h"
#include "PointCD.h"
#include <unordered_map>

class AnimationCDPlayer
{
private:
	AnimationCDPlayer() = default; // 1.Don't public constructor function
	static AnimationCDPlayer* instance; // 2. static private instance


	unordered_map<CDType, AnimationCD*> listCD;

public:
	AnimationCDPlayer(const AnimationCDPlayer&) = delete; // 3. delete copy constructor
	static AnimationCDPlayer* getInstance();	  // 4. public function for client code usage


	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
	void addCD(pair<CDType, AnimationCD*> cd);
};