#pragma once
#include "ViewController.h"
#include "WorldMap.h"
#include "Grass.h"
#include "WMario.h"
#include "ScoreBoard.h"

class WorldVC : public ViewController
{
private:
	Map* map;
	Grass* grasses;
	WMario* wMario;

	ScoreBoard* scoreBoard;
public:
	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewDidLoad();
	void viewWillUpdate(float _dt);
	void viewDidRender();

	void adaptData();
};

