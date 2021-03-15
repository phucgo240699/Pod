#include "Man1.h"

void Man1::viewDidLoad()
{
	c1 = new Component(0, 0, 500, 100, new Color(red));
	c2 = new Component(200, 300, 500, 100, new Color(yellow));
	//char* path = new char[20];
	//path = "./Assets/Images/AladdinSpriteSheet.png";
	c3 = new Component(100, 100, L"./Assets/Images/panda.png", new Color(pinkFF00FF));

	//this->addComponent(c1);
	//this->addComponent(c2);
	this->addComponent(c1);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	if (_keyType == KeyType::up) {
		c1->jumpTo(c1->getBounds()->left, c1->getBounds()->top - 1);
	}
	if (_keyType == KeyType::down) {
		c1->jumpTo(c1->getBounds()->left, c1->getBounds()->top + 1);
	}
	if (_keyType == KeyType::left) {
		c1->jumpTo(c1->getBounds()->left - 1, c1->getBounds()->top);
	}
	if (_keyType == KeyType::right) {
		c1->jumpTo(c1->getBounds()->left + 1, c1->getBounds()->top);
	}
}
