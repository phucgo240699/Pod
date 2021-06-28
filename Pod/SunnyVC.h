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

	int beginGroundId = 0, endGroundId = 14;
	vector<Ground*>* grounds;

	int beginBlockId = 15, endBlockId = 26;
	vector<Block*>* blocks;

	int beginGoldenBrickId = 27, endGoldenBrickId = 45;
	vector<GoldenBrick*>* goldenBricks;

	int beginSuperMushroomId = 46, endSuperMushroomId = 46;
	int beginGiftBrickId = 47, endGiftBrickId = 50;
	vector<GiftBrick*>* giftBricks;

	int beginGreenPipeId = 51, endGreenPipeId = 54;
	vector<GreenPipe*>* greenPipes;


	// Enemies
	int beginGoombaId = 55, endGoombaId = 55;
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

	void adaptData();
	void adaptAnimation();
	void adaptToGrid();
};