#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "SunnyMap.h"
#include "StaticAnim.h"
#include "AnimationBundle.h"
#include "Goomba.h"
#include "GreenPipe.h"
#include "Block.h"

class SunnyVC : public ViewController
{
private:
	int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;

	int beginGroundId = 0, endGroundId = 12;
	vector<Ground*>* grounds;

	int beginBlockId = 13, endBlockId = 23;
	vector<Block*>* blocks;

	int beginGoldenBrickId = 24, endGoldenBrickId = 42;
	vector<GoldenBrick*>* goldenBricks;

	int beginGiftBrickId = 43, endGiftBrickId = 46;
	vector<GiftBrick*>* giftBricks;

	int beginGreenPipe = 47, endGreenPipe = 50;
	vector<GreenPipe*>* greenPipes;

	// Enemies
	int beginGoombaId = 51, endGoombaId = 51;
	unordered_set<Goomba*>* goombas;

	tuple<bool, float, vector<CollisionEdge>> mario_ground_collision;
public:
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
	void adaptToGrid();
};