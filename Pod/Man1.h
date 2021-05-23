#pragma once
#include "ViewController.h"
#include "Ground.h"
#include "Mario.h"

class Man1 : public ViewController
{
private:
	Ground* ground;
public:
	void viewDidLoad();
	void viewDidUpdate(float _dt);
};

