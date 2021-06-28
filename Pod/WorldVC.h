#pragma once
#include "ViewController.h"
#include "WorldMap.h"
#include "StaticAnim.h"
#include "WMario.h"
#include "ScoreBoard.h"
#include "WTurtle.h"

class WorldVC : public ViewController
{
private:
	Map* map;
	StaticAnim* grasses;
	StaticAnim* helpLabel;
	WMario* wMario;
	WTurtle* wTurtle;

public:
	// De init
	~WorldVC();

	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewDidLoad();
	void viewWillUpdate(float _dt);
	void viewWillRender();
	void viewDidRender();

	void adaptData();
	void adaptAnimation();
};

