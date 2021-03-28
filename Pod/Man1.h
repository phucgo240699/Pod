#pragma once
#include "ViewController.h"
#include "Mario.h"

class Man1 : public ViewController
{
private:
public:
	void viewDidLoad();
	void viewReceiveKeyDown(KeyType _keyType);
	void viewReceiveKeyUp();
};

