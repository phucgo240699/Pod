#pragma once
#include "Ground.h"
#include "Coin.h"
#include "ViewController.h"
#include "Mario.h"

class UndergroundVC : public ViewController
{
private:
	Mario* mario;
	Map* map;

	int beginGroundId, endGroundId;
	vector<Ground*>* grounds;

	int beginCoinId, endCoinId;
	unordered_set<Coin*>* coins;

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

	void adaptRangeID(vector<string> data, char seperator);
	void adaptData();
	void adaptAnimation();
	void adaptToGrid();
};