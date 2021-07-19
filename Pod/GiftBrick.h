#pragma once
#include "Component.h"
#include "Camera.h"
#include "GiftBrickState.h"
#include "AnimationBundle.h"
#include "SuperMushroom.h"
#include "Grid.h"
#include "GiftType.h"
#include "SuperLeaf.h"

class GiftBrick : public Component
{
private:
	GiftBrickState state = FULLGIFTBRICK;
	Animation* boxAnimation, * coinAnimation, * pointAnimation;
	SuperMushroom* superMushroom;
	SuperLeaf* superLeaf;
	GiftType giftType;

	int beginBoxJumpUp, endBoxJumpUp;
	int beginCoinJumpUp, endCoinJumpUp, coinY, pointY;
	bool isBoxDropDown = false, isCoinDropDown = false, isPointsStartPopUp = false;	

public:
	GiftBrick(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	GiftBrick(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY);

	void loadInfo(string line, char seperator);

	// Getter
	SuperMushroom* getSuperMushroom();
	SuperLeaf* getSuperLeaf();
	GiftBrickState getState();
	GiftType getGiftType();

	// Setter
	void setSuperMushroomState(SuperMushroomState _state);
	void setSuperLeafState(SuperLeafState _state);
	void setState(GiftBrickState _state);
	void setGiftType(GiftType _giftType);
	void setGiftType(int _giftCode);

	void Update(float _dt);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

