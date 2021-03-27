#pragma once
#include "ViewController.h"
#include "Mario.h"

class Man1 : public ViewController
{
private:
	Mario* mainCharacter;
public:
	void viewDidLoad();
	void viewReceiveKeyDown(KeyType _keyType);
	void viewReceiveKeyUp();
};

