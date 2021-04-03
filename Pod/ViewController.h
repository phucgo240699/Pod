#pragma once
#include <vector>
#include "Setting.h"
#include "Component.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Map.h"

class ViewController
{
protected:
	Component* mainCharacter;
	Map* map;

public:
	// Init
	ViewController();

	// De Init
	~ViewController();

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewReceiveKeyDown(KeyType _keyType);
	virtual void viewReceiveKeyUp();
	virtual void viewWillUpdate(int _dt);
	virtual void viewDidUpdate(int _dt);
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();
};

