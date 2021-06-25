#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "SunnyMap.h"
#include "StaticAnim.h"
#include "AnimationBundle.h"
#include "Goomba.h"
#include "GreenPipe.h"

class SunnyVC : public ViewController
{
private:
	int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;

	int beginGroundId = 0, endGroundId = 12;
	vector<Ground*>* grounds;

	int beginGoldenBrickId = 13, endGoldenBrickId = 31;
	vector<GoldenBrick*>* goldenBricks;

	int beginGiftBrickId = 32, endGiftBrickId = 35;
	vector<GiftBrick*>* giftBricks;

	int beginGreenPipe = 36, endGreenPipe = 39;
	vector<GreenPipe*>* greenPipes;

	// Enemies
	int beginGoombaId = 40, endGoombaId = 40;
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