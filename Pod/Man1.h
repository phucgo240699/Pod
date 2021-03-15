#pragma once
#include "ViewController.h"
#include "Image.h"

class Man1 : public ViewController
{
private:
	View* c1;
public:
	void viewDidLoad();
	void viewReceiveKeyDown(KeyType _keyType);
};

