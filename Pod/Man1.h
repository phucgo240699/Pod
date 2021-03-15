#pragma once
#include "ViewController.h"

class Man1 : public ViewController
{
private:
	Component* c1;
	Component* c2;
	Component* c3;
public:
	void viewDidLoad();
	void viewReceiveKeyDown(KeyType _keyType);
};

