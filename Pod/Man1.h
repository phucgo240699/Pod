#pragma once
#include "ViewController.h"
#include "Ground.h"
#include "Mario.h"

class Man1 : public ViewController
{
private:
	Mario* mainCharacter;
	Map* map;
	Ground* ground;
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
};

