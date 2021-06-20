#pragma once
#include "Setting.h"
#include "MainCharacter.h"
#include "KeyType.h"
#include "Camera.h"
#include "Map.h"
#include "Grid.h"

class ViewController
{
protected:

public:

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewReceiveKeyUp();
	virtual void viewReceiveKeyUp(vector<KeyType> _keyTypes);
	virtual void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	virtual void viewWillUpdate(float _dt);
	virtual void viewDidUpdate(float _dt);
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();
};

