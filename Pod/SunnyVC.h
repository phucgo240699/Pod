#pragma once
#include "ViewController.h"
#include "Ground.h"
#include "Mario.h"
#include "SectionFile.h"
#include "GiftBrick.h"
#include "SunnyMap.h"
#include "ScoreBoard.h"
#include "StaticAnim.h"
#include "GoldenBrick.h"
#include "AnimationBundle.h"
#include "Goomba.h"

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

	// Enemies
	int beginGoombaId = 36, endGoombaId = 37;
	vector<Goomba*>* goombas;


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
	void adaptAnimationBundle();
	void adaptToGrid();


	void handleMarioGroundCollision(Component* _ground, float _dt);
	void handleMarioGoldenBrickCollision(Component* _goldenBrick, float _dt);
	void handleMarioGiftBrickCollision(GiftBrick* _goldenBrick, float _dt);
};