#pragma once
#include "ViewController.h"
#include "WorldMap.h"

class WorldVC : public ViewController
{
private:
	WorldMap* map;
public:
	void viewDidLoad();
	void viewWillUpdate(float _dt);
	void viewDidRender();

	void adaptData();
};

