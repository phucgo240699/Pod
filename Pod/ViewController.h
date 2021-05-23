	#pragma once
#include <vector>
#include "Setting.h"
#include "MainCharacter.h"
#include "KeyType.h"
#include "Camera.h"
#include "Map.h"

class ViewController
{
protected:
	MainCharacter* mainCharacter;
	Map* map;

public:
	// Init
	ViewController();

	// De Init
	~ViewController();

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewReceiveKeyUp();
	virtual void viewReceiveKeyUp(KeyType _keyType);
	virtual void viewReceiveKeyDown(KeyType _keyType);
	virtual void viewWillUpdate(float _dt);
	virtual void viewDidUpdate(float _dt);
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();
};

