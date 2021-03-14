#pragma once
#include "Color.h"
#include <vector>
#include "Rect.h"
#include "Setting.h"
#include "Component.h"

class ViewController
{
protected:
	Component* background;
	vector<Component*> components;

public:

	// Getter
	Component* getBackground();

	// Setter
	void setBackground(Component* _background);

	// Life cycle
	virtual void viewDidLoad();
	virtual void viewWillUpdate();
	virtual void viewDidUpdate();
	virtual void viewWillRender();
	virtual void viewDidRender();
	virtual void viewWillRelease();

	virtual void addComponent(Component* _component);
};

