#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "StaticAnim.h"
#include "AnimationBundle.h"
#include "Goomba.h"
#include "Koopa.h"
#include "AnimationCDPlayer.h"
#include "FireFlower.h"
#include "Flower.h"
#include "FireBall.h"
#include "Coin.h"
#include "Item.h"

class SunnyVC : public ViewController
{
private:
	//int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;

	int beginGroundId, endGroundId;
	vector<Ground*>* grounds;

	int beginBlockId, endBlockId;
	vector<Block*>* blocks;

	int beginGoldenBrickId, endGoldenBrickId;
	unordered_set<GoldenBrick*>* goldenBricks;

	int beginSuperMushroomId, endSuperMushroomId;
	int beginSuperLeafId, endSuperLeafId;
	int beginGiftBrickId, endGiftBrickId;
	vector<GiftBrick*>* giftBricks;


	int beginFireFlowerId, endFireFlowerId;
	int beginFireFlowerBallId, endFireFlowerBallId;
	unordered_set<FireFlower*>* fireFlowers;

	int beginFlowerId, endFlowerId;
	unordered_set<Flower*>* flowers;

	int beginGreenPipeId, endGreenPipeId, componentIdToUnderground, leftAnchorGreenPipeToPassThrough, rightAnchorGreenPipeToPassThrough;
	vector<GreenPipe*>* greenPipes;

	int beginFireBallId, endFireBallId;
	//vector<FireBall*>* fireBalls;

	int beginCoinId, endCoinId;
	unordered_set<Coin*>* coins;

	int beginPButtonId, endPButtonId;

	int beginItemId, endItemId;
	unordered_set<Item*>* items;


	//
	// Enemies
	//

	// Goombas
	int beginGoombaId, endGoombaId;
	unordered_set<Goomba*>* goombas;

	// Koopas
	int beginKoopaId, endKoopaId;
	unordered_set<Koopa*>* koopas;

	bool isPressedPButton = false, isRestoredGoldenBrick = false, isRestoredCamera = false;
	int countDownGoldenBrickBeingCoin = 340;
	float camShakingValue = 2;


	// PoppingUp
	float leftAnchorMarioPoppingUpFromPipe, bottomAnchorMarioPoppingUpFromPipe;

public:
	// Getter
	bool getIsPressedPButton();
	bool getIsRestoredGoldenBrick();
	Mario* getMario();
	float getLeftAnchorMarioPoppingUpFromPipe();
	float getBottomAnchorMarioPoppingUpFromPipe();



	// Setter
	void setIsPressedPButton(bool _isPressedPButton);
	void setIsRestoredGoldenBrick(bool _isRestoreGoldenBrick);
	void setMario(Mario* _mario);

	// De init
	//~SunnyVC();


	void viewDidLoad();
	void viewReceiveKeyUp();
	void viewReceiveKeyUp(vector<KeyType> _keyTypes);
	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewWillUpdate(float _dt);
	void viewUpdate(float _dt);
	void viewDidUpdate(float _dt);
	void viewWillRender();
	void viewDidRender();
	void viewWillRelease();

	void adaptRangeID(vector<string> data, char seperator);
	void adaptData();
	void adaptAnimation();
	void adaptToGrid();
};