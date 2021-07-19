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
	return this->animations->at(18);
}

Animation AnimationBundle::getMarioWalking()
{
	return this->animations->at(19);
}

Animation AnimationBundle::getMarioDropping()
{
	return this->animations->at(20);
}

Animation AnimationBundle::getMarioJumping()
{
	return this->animations->at(20);
}

Animation AnimationBundle::getMarioDie()
{
	return this->animations->at(21);
}

Animation AnimationBundle::getMarioConverting()
{
	return this->animations->at(22);
}

Animation AnimationBundle::getGoldenBrick()
{
	return this->animations->at(0);
}

Animation AnimationBundle::getFullGiftBrick()
{
	return this->animations->at(1);
}

Animation AnimationBundle::getEmptyGiftBrick()
{
	return this->animations->at(2);
}

Animation AnimationBundle::getCoinGiftBrick()
{
	return this->animations->at(3);
}

Animation AnimationBundle::get100Points()
{
	return this->animations->at(13);
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

Animation AnimationBundle::getSuperMushroom()
{
	return this->animations->at(8);
}

Animation AnimationBundle::getSuperMarioStanding()
{
	return this->animations->at(23);
}

Animation AnimationBundle::getSuperMarioWalking()
{
	return this->animations->at(24);
}

Animation AnimationBundle::getSuperMarioDropping()
{
	return this->animations->at(25);
}

Animation AnimationBundle::getSuperMarioJumping()
{
	return this->animations->at(25);
}

Animation AnimationBundle::getMarioScalingUp()
{
	return this->animations->at(26);
}

Animation AnimationBundle::getMarioScalingDown()
{
	return this->animations->at(27);
}

Animation AnimationBundle::getSuperMarioConverting()
{
	return this->animations->at(28);
}

Animation AnimationBundle::getMarioFireStanding()
{
	return this->animations->at(29);
}

Animation AnimationBundle::getMarioFireWalking()
{
	return this->animations->at(30);
}

Animation AnimationBundle::getMarioFireDropping()
{
	return this->animations->at(31);
}

Animation AnimationBundle::getMarioFireJumping()
{
	return this->animations->at(31);
}

Animation AnimationBundle::getMarioFireDie()
{
	return this->animations->at(32);
}

Animation AnimationBundle::getMarioFireConverting()
{
	return this->animations->at(33);
}

Animation AnimationBundle::getSuperMarioFireStanding()
{
	return this->animations->at(34);
}

Animation AnimationBundle::getSuperMarioFireWalking()
{
	return this->animations->at(35);
}

Animation AnimationBundle::getSuperMarioFireDropping()
{
	return this->animations->at(36);
}

Animation AnimationBundle::getSuperMarioFireJumping()
{
	return this->animations->at(36);
}

Animation AnimationBundle::getMarioFireScalingUp()
{
	return this->animations->at(37);
}

Animation AnimationBundle::getMarioFireScalingDown()
{
	return this->animations->at(38);
}

Animation AnimationBundle::getSuperMarioFireConverting()
{
	return this->animations->at(39);
}

Animation AnimationBundle::getKoopaGreenMoving()
{
	return this->animations->at(40);
}

Animation AnimationBundle::getKoopaGreenShrinkage()
{
	return this->animations->at(41);
}

Animation AnimationBundle::getKoopaGreenShrinkageMoving()
{
	return this->animations->at(42);
}

Animation AnimationBundle::getKoopaGreenShrinkageShaking()
{
	return this->animations->at(43);
}

Animation AnimationBundle::getThrownAwayGoomba()
{
	return this->animations->at(44);
}

Animation AnimationBundle::getFlashLight()
{
	return this->animations->at(45);
}

Animation AnimationBundle::getSuperLeaf()
{
	return this->animations->at(46);
}

Animation AnimationBundle::getCloudEffect()
{
	return this->animations->at(47);
}

Animation AnimationBundle::getSuperMarioFlyingStanding()
{
	return this->animations->at(48);
}

Animation AnimationBundle::getSuperMarioFlyingFireStanding()
{
	return this->animations->at(53);
}

Animation AnimationBundle::getSuperMarioFlyingFireWalking()
{
	return this->animations->at(54);
}

Animation AnimationBundle::getSuperMarioFlyingFireJumping()
{
	return this->animations->at(55);
}

Animation AnimationBundle::getSuperMarioFlyingFireDropping()
{
	return this->animations->at(56);
}

Animation AnimationBundle::getSuperMarioFlyingFireConverting()
{
	return this->animations->at(57);
}

Animation AnimationBundle::getRedFireFlowerStandingLookUp()
{
	return this->animations->at(58);
}

Animation AnimationBundle::getRedFireFlowerStandingLookDown()
{
	return this->animations->at(59);
}

Animation AnimationBundle::getRedFireFlowerGrowingUp()
{
	return this->animations->at(60);
}

Animation AnimationBundle::getRedFireFlowerDropping()
{
	return this->animations->at(61);
}

Animation AnimationBundle::getRedFlower()
{
	return this->animations->at(62);
}

Animation AnimationBundle::getGreenFireFlowerStandingLookUp()
{
	return this->animations->at(63);
}

Animation AnimationBundle::getGreenFireFlowerStandingLookDown()
{
	return this->animations->at(64);
}

Animation AnimationBundle::getGreenFireFlowerGrowingUp()
{
	return this->animations->at(65);
}

Animation AnimationBundle::getGreenFireFlowerDropping()
{
	return this->animations->at(66);
}

Animation AnimationBundle::getGreenFlower()
{
	return this->animations->at(67);
}

Animation AnimationBundle::getFireFlowerBall()
{
	return this->animations->at(68);
}

Animation AnimationBundle::getFireBall()
{
	return this->animations->at(68);
}

Animation AnimationBundle::getRedFireFlowerStandingLookUpHalfSize()
{
	return this->animations->at(69);
}

Animation AnimationBundle::getRedFireFlowerStandingLookDownHalfSize()
{
	return this->animations->at(70);
}

Animation AnimationBundle::getRedFireFlowerGrowingUpHalfSize()
{
	return this->animations->at(71);
}

Animation AnimationBundle::getRedFireFlowerDroppingHalfSize()
{
	return this->animations->at(72);
}

Animation AnimationBundle::getRedFlowerHalfSize()
{
	return this->animations->at(73);
}

Animation AnimationBundle::getGreenFireFlowerStandingLookUpHalfSize()
{
	return this->animations->at(74);
}

Animation AnimationBundle::getGreenFireFlowerStandingLookDownHalfSize()
{
	return this->animations->at(75);
}

Animation AnimationBundle::getGreenFireFlowerGrowingUpHalfSize()
{
	return this->animations->at(76);
}

Animation AnimationBundle::getGreenFireFlowerDroppingHalfSize()
{
	return this->animations->at(77);
}

Animation AnimationBundle::getGreenFlowerHalfSize()
{
	return this->animations->at(78);
}

Animation AnimationBundle::getKoopaRedThrownAway()
{
	return this->animations->at(79);
}

Animation AnimationBundle::getKoopaGreenThrownAway()
{
	return this->animations->at(80);
}

Animation AnimationBundle::getFireBallSplash()
{
	return this->animations->at(81);
}

Animation AnimationBundle::getSuperMarioFlyingFireTurningAround()
{
	return this->animations->at(83);
}

Animation AnimationBundle::getSuperMarioFlyingTurningAround()
{
	return this->animations->at(82);
}

Animation AnimationBundle::getSuperMarioPreFlyingUp()
{
	return this->animations->at(84);
}

Animation AnimationBundle::getSuperMarioFlyingUp()
{
	return this->animations->at(85);
}

Animation AnimationBundle::getSuperMarioFirePreFlyingUp()
{
	return this->animations->at(86);
}

Animation AnimationBundle::getSuperMarioFireFlyingUp()
{
	return this->animations->at(87);
}

Animation AnimationBundle::getGoldenBrickFragment()
{
	return this->animations->at(89);
}

Animation AnimationBundle::getPButtonOn()
{
	return this->animations->at(90);
}

Animation AnimationBundle::getPButtonOff()
{
	return this->animations->at(91);
}

Animation AnimationBundle::getSuperMarioFlyingWalking()
{
	return this->animations->at(49);
}

Animation AnimationBundle::getSuperMarioFlyingJumping()
{
	return this->animations->at(50);
}

Animation AnimationBundle::getSuperMarioFlyingDropping()
{
	return this->animations->at(51);
}

Animation AnimationBundle::getSuperMarioFlyingConverting()
{
	return this->animations->at(52);
}

Animation AnimationBundle::getKoopaMoving()
{
	return this->animations->at(9);
}

Animation AnimationBundle::getKoopaShrinkage()
{
	return this->animations->at(10);
}

Animation AnimationBundle::getKoopaShrinkageMoving()
{
	return this->animations->at(11);
}

Animation AnimationBundle::getKoopaShrinkageShaking()
{
	return this->animations->at(12);
}

Animation AnimationBundle::get200Points()
{
	return this->animations->at(14);
}

Animation AnimationBundle::getPoints(int points)
{	
	if (points == 200) {
		this->get200Points();
	}
	else if (points == 400) {
		this->get400Points();
	}
	else if (points == 800) {
		this->get800Points();
	}
	else if (points == 1000) {
		this->get1000Points();
	}
	else {
		return this->get100Points();
	}
}

Animation AnimationBundle::get400Points()
{
	return this->animations->at(15);
}

Animation AnimationBundle::get800Points()
{
	return this->animations->at(16);
}

Animation AnimationBundle::get1000Points()
{
	return this->animations->at(17);
}

Animation AnimationBundle::getCoin()
{
	return this->animations->at(88);
}