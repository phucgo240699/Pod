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

	int beginGiftBrickId = 46, endGiftBrickId = 49;
	vector<GiftBrick*>* giftBricks;

	int beginGreenPipeId = 50, endGreenPipeId = 53;
	vector<GreenPipe*>* greenPipes;

	// Enemies
	int beginGoombaId = 54, endGoombaId = 54;
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
	void adaptAnimation();
	void adaptToGrid();
};