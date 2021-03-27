#pragma once
#include <vector>
#include "Setting.h"
#include "Component.h"
#include "Keyboard.h"

class ViewController
{
protected:
	vector<Component*> components;

public:
	// Init
	ViewController();

	// De Init
	~ViewController();

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewReceiveKeyDown(KeyType _keyType);
	virtual void viewReceiveKeyUp();
	virtual void viewWillUpdate();
	virtual void viewDidUpdate();
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();

	virtual void addComponent(Component* _component);
};

