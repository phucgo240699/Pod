#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "Enemy.h"
#include "KoopaState.h"
#include "Camera.h"
#include "Grid.h"
#include "AnimationCDPlayer.h"
#include "GiftBrick.h"


class Mario; // Say Goomba exists without defining it.
class Goomba;
class FireBall;

class Koopa : public Enemy
{
private:
	Animation* animation;// , pointAnimation = Animation(0, 0, 0);
	KoopaState state;

	bool firstCheckAnim = true;
	int oldFrameHeight, oldFrameWidth;
	int newFrameHeight, newFrameWidth;

	int leftAnchor, rightAnchor;
	//float endPointJumpUp, pointX, pointY = -std::numeric_limits<float>::infinity();

	int countDown = 30, originCountDown = 30; // countDown to switch from standing to shaking, and from shaking to moving

	bool isFlip = false, isGreenMode = false;

	// Thrown away
	float thrownX, startThrownY;

public:
	// Init
	Koopa(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Koopa(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	void loadInfo(string line, char seperator);

	// Getter
	KoopaState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	bool getIsFlip();
	bool getIsStandOnSurface();
	bool getHasCollideMario();
	bool getIsGreenMode();

	// Setter
	void setState(KoopaState _state);
	void setIsFlip(bool _isFlip);
	//void setPointX(float _pointX);
	//void setPointY(float _pointY);
	//void setEndPointJumpUp(float _endPointJumpUp);
	void setupPointAnimPosition();
	void setHasCollideMario(bool _hasCollideMario);
	void setIsGreenMode(bool _isGreenMode);

	void convertMovingState();
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);

	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleGiftBrickCollision(GiftBrick* _giftBrick, Mario* _mario, float _dt);
	void handleBlockCollision(Component* _block, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
	void handleMarioCollision(Mario* _mario, float _dt);
	void handleFireBallCollision(FireBall* _fireBall, float _dt);
};

#endif // !KOOPA