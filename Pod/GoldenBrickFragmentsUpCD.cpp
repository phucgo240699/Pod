#include "GoldenBrickFragmentsUpCD.h"
#include "Camera.h"

GoldenBrickFragmentsUpCD::GoldenBrickFragmentsUpCD(int _originXLeft, int _originXRight, int _originYTop, int _originYBottom) : AnimationCD(Animation(0,0,0))
{
	AnimationCD::AnimationCD(Animation(0, 0, 0));
	this->originYTop = _originYTop;
	this->originYBottom = _originYBottom;
	this->originXLeft = _originXLeft;
	this->originXRight = _originXRight;
	this->xLeft = 0;
	this->xRight = 0;

	this->brickFragment1 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
	this->brickFragment2 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
	this->brickFragment3 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
	this->brickFragment4 = new Animation(AnimationBundle::getInstance()->getGoldenBrickFragment());
}

//GoldenBrickFragmentsUpCD::~GoldenBrickFragmentsUpCD()
//{
//	delete& xLeft;
//	delete& xRight;
//	delete& yTop;
//	delete& yBottom;
//	delete brickFragment1;
//	delete brickFragment2;
//	delete brickFragment3;
//	delete brickFragment4;
//}

void GoldenBrickFragmentsUpCD::Update(float _dt)
{
	this->brickFragment1->Update(_dt);
	this->brickFragment2->Update(_dt);
	this->brickFragment3->Update(_dt);
	this->brickFragment4->Update(_dt);

	xLeft -= 2;
	xRight += 2;

	y1 = (-1 * (48 - (pow(xLeft + 24, 2) / 12)));
	y2 = (-1 * (48 - (pow(xRight - 24, 2) / 12)));
	y3 = (-1 * (32 - (pow(xLeft + 16, 2) / 8)));
	y4 = (-1 * (32 - (pow(xRight - 16, 2) / 8)));
	
	cameraLimitY = Camera::getInstance()->getLimitY();
	if (y1 > cameraLimitY && y2 > cameraLimitY && y3 > cameraLimitY && y4 > cameraLimitY) {
		this->setIsFinish(true);
	}
}

void GoldenBrickFragmentsUpCD::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	position.x = originXLeft + xLeft;
	position.y = originYTop +  this->y1;
	Drawing::getInstance()->draw(_texture, this->brickFragment1->getCurrentFrame(), this->position);

	position.x = originXRight + xRight;
	position.y = originYTop + this->y2;
	Drawing::getInstance()->draw(_texture, this->brickFragment2->getCurrentFrame(), this->position);

	position.x = originXLeft + xLeft;
	position.y = originYBottom + this->y3;
	Drawing::getInstance()->draw(_texture, this->brickFragment3->getCurrentFrame(), this->position);

	position.x = originXRight + xRight;
	position.y = originYBottom + this->y4;
	Drawing::getInstance()->draw(_texture, this->brickFragment4->getCurrentFrame(), this->position);
}
