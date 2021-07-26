#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "AnimationBundle.h"
#include "AnimationCDPlayer.h"
#include "MusicBox.h"
#include "BoomerangBro.h"
#include "Boss.h"
#include "Bomb.h"

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

	// Music box
	int beginMusicBoxId, endMusicBoxId;
	vector<MusicBox*>* musicBoxes;

	// Bomerang Bro
	int beginBoomerangBroId, endBoomerangBroId;
	int beginBoomerangId, endBoomerangId;
	unordered_set<BoomerangBro*>* boomerangBros;

	int beginBossId, endBossId;
	unordered_set<Boss*>* bosses;

	int beginBombId, endBombId;
	vector<Bomb*>* bombs;

	int beginFireBallId, endFireBallId;

	int leftAnchorDroppingFromCloudy, topAnchorDroppingFromCloudy;

public:
	// Getter
	Mario* getMario();
	int getLeftAnchorDroppingFromCloudy();
	int getTopAnchorDroppingFromCloudy();


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