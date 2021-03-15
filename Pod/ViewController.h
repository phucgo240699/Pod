#pragma once
#include "Color.h"
#include <vector>
#include "Setting.h"
#include "Component.h"
#include "Keyboard.h"

class ViewController
{
protected:
	Component* background;
	vector<Component*> components;

public:
	// De Init
	~ViewController();

	// Getter
	Component* getBackground();

	// Setter
	void setBackground(Component* _background);

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

