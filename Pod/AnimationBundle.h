#pragma once
#include "Animation.h"

class AnimationBundle
{
private:
	AnimationBundle() = default; // 1.Don't public constructor function
	static AnimationBundle* instance; // 2. static private instance

	vector<Animation>* animations;

public:
	AnimationBundle(const AnimationBundle&) = delete; // 3. delete copy constructor
	static AnimationBundle* getInstance();	  // 4. public function for client code usage


	void loadAnimations(vector<string> data, char endSperator, char seperator);

	//Animation getAnimationAt(int index);

	// World Scene
	Animation getWMario();
	Animation getGrasses();
	Animation getHelpLabel();
	Animation getWTurtle();

	// Sunny Scene
	Animation getMarioStanding();
	Animation getMarioWalking();
	Animation getMarioDropping();
	Animation getMarioJumping();
	Animation getMarioDie();
	Animation getGoldenBrick();
	Animation getFullGiftBrick();
	Animation getEmptyGiftBrick();
	Animation getCoin();
	Animation get100Points();
	Animation getGoombaMoving();
	Animation getTrampledGoomba();
	Animation getGreenPipe3Floor();
	Animation getGreenPipe2Floor();
	Animation getSuperMushroom();
	Animation getSuperMarioStanding();
	Animation getSuperMarioWalking();
	Animation getSuperMarioDropping();
	Animation getSuperMarioJumping();
	Animation getMarioScalingUp();
	Animation getMarioScalingDown();
};

