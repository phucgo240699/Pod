#pragma once
#include "ViewController.h"
#include "WorldMap.h"
#include "StaticAnim.h"
#include "WMario.h"
#include "ScoreBoard.h"

class WorldVC : public ViewController
{
private:
	Map* map;
	StaticAnim* grasses;
	StaticAnim* helpLabel;
	WMario* wMario;

	ScoreBoard* scoreBoard;
public:
	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewDidLoad();
	void viewWillUpdate(float _dt);
	void viewDidRender();

	void adaptData();
};

