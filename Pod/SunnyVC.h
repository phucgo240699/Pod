#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "SunnyMap.h"
#include "StaticAnim.h"
#include "AnimationBundle.h"
#include "Goomba.h"

class SunnyVC : public ViewController
{
private:
	int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;

	int beginGroundId, endGroundId;
	vector<Ground*>* grounds;

	int beginBlockId, endBlockId;
	vector<Block*>* blocks;

	int beginGoldenBrickId, endGoldenBrickId;
	vector<GoldenBrick*>* goldenBricks;

	int beginSuperMushroomId, endSuperMushroomId;
	int beginGiftBrickId, endGiftBrickId;
	vector<GiftBrick*>* giftBricks;

	int beginGreenPipeId, endGreenPipeId;
	vector<GreenPipe*>* greenPipes;


	// Enemies
	int beginGoombaId, endGoombaId;
	unordered_set<Goomba*>* goombas;
public:
	// De init
	~SunnyVC();

	void viewDidLoad();
	void viewReceiveKeyUp();
	void viewReceiveKeyUp(vector<KeyType> _keyTypes);
	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewWillUpdate(float _dt);
	void viewDidUpdate(float _dt);
	void viewWillRender();
	void viewDidRender();
	void viewWillRelease();

	void adaptRangeID(vector<string> data, char seperator);
	void adaptData();
	void adaptAnimation();
	void adaptToGrid();
};