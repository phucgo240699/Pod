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
	Animation getGoldenBrick();
	Animation getFullGiftBrick();
	Animation getEmptyGiftBrick();
	Animation getCoinGiftBrick();
	Animation getGoombaMoving();
	Animation getTrampledGoomba();
	Animation getGreenPipe3Floor();
	Animation getGreenPipe2Floor();
	Animation getSuperMushroom();
	Animation getKoopaMoving();
	Animation getKoopaShrinkage();
	Animation getKoopaShrinkageMoving();
	Animation getKoopaShrinkageShaking();
	Animation get100Points();
	Animation get200Points();
	Animation get400Points();
	Animation get800Points();
	Animation get1000Points();
	Animation getPoints(int points);

	// Mario
	Animation getMarioStanding();
	Animation getMarioWalking();
	Animation getMarioDropping();
	Animation getMarioJumping();
	Animation getMarioDie();
	Animation getMarioConverting();
	Animation getSuperMarioStanding();
	Animation getSuperMarioWalking();
	Animation getSuperMarioDropping();
	Animation getSuperMarioJumping();
	Animation getMarioScalingUp();
	Animation getMarioScalingDown();
	Animation getSuperMarioConverting();
	Animation getMarioFireStanding();
	Animation getMarioFireWalking();
	Animation getMarioFireDropping();
	Animation getMarioFireJumping();
	Animation getMarioFireDie();
	Animation getMarioFireConverting();
	Animation getSuperMarioFireStanding();
	Animation getSuperMarioFireWalking();
	Animation getSuperMarioFireDropping();
	Animation getSuperMarioFireJumping();
	Animation getMarioFireScalingUp();
	Animation getMarioFireScalingDown();
	Animation getSuperMarioFireConverting();

	Animation getKoopaGreenMoving();
	Animation getKoopaGreenShrinkage();
	Animation getKoopaGreenShrinkageMoving();
	Animation getKoopaGreenShrinkageShaking();

	Animation getThrownAwayGoomba();
	Animation getFlashLight();
	Animation getSuperLeaf();
	Animation getCloudEffect();

	Animation getSuperMarioFlyingStanding();
	Animation getSuperMarioFlyingWalking();
	Animation getSuperMarioFlyingJumping();
	Animation getSuperMarioFlyingDropping();
	Animation getSuperMarioFlyingConverting();

	Animation getSuperMarioFlyingFireStanding();
	Animation getSuperMarioFlyingFireWalking();
	Animation getSuperMarioFlyingFireJumping();
	Animation getSuperMarioFlyingFireDropping();
	Animation getSuperMarioFlyingFireConverting();

	Animation getRedFireFlowerStandingLookUp();
	Animation getRedFireFlowerStandingLookDown();
	Animation getRedFireFlowerGrowingUp();
	Animation getRedFireFlowerDropping();
	Animation getRedFlower();


	Animation getGreenFireFlowerStandingLookUp();
	Animation getGreenFireFlowerStandingLookDown();
	Animation getGreenFireFlowerGrowingUp();
	Animation getGreenFireFlowerDropping();
	Animation getGreenFlower();

	Animation getFireFlowerBall();
	Animation getFireBall();

	Animation getRedFireFlowerStandingLookUpHalfSize();
	Animation getRedFireFlowerStandingLookDownHalfSize();
	Animation getRedFireFlowerGrowingUpHalfSize();
	Animation getRedFireFlowerDroppingHalfSize();
	Animation getRedFlowerHalfSize();

	Animation getGreenFireFlowerStandingLookUpHalfSize();
	Animation getGreenFireFlowerStandingLookDownHalfSize();
	Animation getGreenFireFlowerGrowingUpHalfSize();
	Animation getGreenFireFlowerDroppingHalfSize();
	Animation getGreenFlowerHalfSize();

	Animation getKoopaRedThrownAway();
	Animation getKoopaGreenThrownAway();

	Animation getFireBallSplash();

	Animation getSuperMarioFlyingTurningAround();
	Animation getSuperMarioFlyingFireTurningAround();

	Animation getSuperMarioPreFlyingUp();
	Animation getSuperMarioFlyingUp();
	Animation getSuperMarioFirePreFlyingUp();
	Animation getSuperMarioFireFlyingUp();

	Animation getCoin();
	Animation getGoldenBrickFragment();
	Animation getPButtonOn();
	Animation getPButtonOff();
};

