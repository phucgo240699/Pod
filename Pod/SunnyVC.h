#pragma once
#include "ViewController.h"
#include "Ground.h"
#include "Mario.h"
#include "SectionFile.h"
#include "GiftBrick.h"
#include "SunnyMap.h"

class SunnyVC : public ViewController
{
private:
	Mario* mario;
	Map* map;
	vector<Ground*>* grounds;
	int currentGroundIndex = 0; // this is the ground that mario is standing on

	GiftBrick* giftBrick;

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
	~SunnyVC();

	void adaptData();
};