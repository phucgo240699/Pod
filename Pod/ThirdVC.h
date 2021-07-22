#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "AnimationBundle.h"
#include "AnimationCDPlayer.h"

class ThirdVC : public ViewController
{
private:
	//int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;

	// Ground
	int beginGroundId, endGroundId;
	vector<Ground*>* grounds;

	// Block
	int beginBlockId, endBlockId;
	vector<Block*>* blocks;

	// GoldenBrick
	int beginGoldenBrickId, endGoldenBrickId;
	unordered_set<GoldenBrick*>* goldenBricks;

	// Gift Brick, SuperMushroom, SuperLeaf
	int beginSuperMushroomId, endSuperMushroomId;
	int beginSuperLeafId, endSuperLeafId;
	int beginGiftBrickId, endGiftBrickId;
	vector<GiftBrick*>* giftBricks;

	// Coin
	int beginCoinId, endCoinId;
	unordered_set<Coin*>* coins;

	// Goombas
	int beginGoombaId, endGoombaId;
	unordered_set<Goomba*>* goombas;

	// Koopas
	int beginKoopaId, endKoopaId;
	unordered_set<Koopa*>* koopas;

	int beginFireBallId, endFireBallId;

public:
	// Getter
	Mario* getMario();



	// Setter
	void setMario(Mario* _mario);

	// De init


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