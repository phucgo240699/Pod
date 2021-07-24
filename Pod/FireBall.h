#pragma once
#include "Component.h"
#include "AnimationCDPlayer.h"
#include "FireBallState.h"
#include "Block.h"
#include "Goomba.h"
#include "Koopa.h"
#include "FireFlower.h"
#include "Flower.h"
#include "BoomerangBro.h"
#include "ScoreBoard.h"
#include "GoldenBrick.h"

//class Block;
//class Goomba;
//class Koopa;

class FireBall : public Component
{
private:
	Animation* animation;
	FireBallState state;
	float originVx, originVy;
	float originX, originY, topAnchor;
	bool isOutOfGrid = true, isGoDown = true;

public:
	// Init
	FireBall(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);


	// Getter
	FireBallState getState();
	float getWidth();
	float getHeight();
	float getBoundsWidth();
	float getBoundsHeight();
	bool getIsOutOfGrid();
	bool getIsGoDown();


	// Setter
	void setAnimation(Animation* _animation);
	void setState(FireBallState _state);
	void resetToOriginalPosition();
	void setIsOutOfGrid(bool _isOutOfGrid);
	void setIsGoDown(bool _isGoDown);
	void setTopAnchor(bool _topAnchor);

	//void loadInfo(string line, char seperator);
	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);


	// Collision
	void handleHardComponentCollision(Component* _component, float _dt);
	void handleBlockCollision(Block* _block, float _dt);
	void handleGoombaCollision(Goomba* _goomba, float _dt);
	void handleKoopaCollision(Koopa* _koopa, float _dt);
	void handleFireFlowerCollision(FireFlower* _fireFlower, float _dt);
	void handleFlowerCollision(Flower* _flower, float _dt);
	void handleGoldenBrickCollision(GoldenBrick* _goldenBrick, float _dt);
	void handleBoomerangBroCollision(BoomerangBro* _boomerangBro, float _dt);
};
