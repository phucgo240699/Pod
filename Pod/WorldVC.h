#pragma once
#include "ViewController.h"
#include "WorldMap.h"
#include "Grass.h"

class WorldVC : public ViewController
{
private:
	WorldMap* map;
	Grass* grasses;
public:
	void viewDidLoad();
	void viewWillUpdate(float _dt);
	void viewDidRender();

	void adaptData();
};

