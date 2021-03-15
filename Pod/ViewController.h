#pragma once
#include <vector>
#include "Setting.h"
#include "View.h"
#include "Keyboard.h"

class ViewController
{
protected:
	Component* background;
	vector<Component*> components;

public:
	// Init
	ViewController();

	// De Init
	~ViewController();

	// Setter
	void setBackgroundColor(D3DCOLOR _color);

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewReceiveKeyDown(KeyType _keyType);
	virtual void viewReceiveKeyUp(KeyType _keyType);
	virtual void viewWillUpdate();
	virtual void viewDidUpdate();
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();

	virtual void addComponent(Component* _component);
};

