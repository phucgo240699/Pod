#include "Man1.h"

Man1::Man1()
{
	RECT* r1 = new RECT();
	RECT* r2 = new RECT();
	r1->top = 0;
	r1->bottom = r1->top + 100;
	r1->left = 0;
	r1->right = r1->left + 500;

	r2->top = 300;
	r2->bottom = r2->top + 100;
	r2->left = 200;
	r2->right = r2->left + 500;
	c1 = new Component(r1, new Color(red));
	c2 = new Component(r2, new Color(yellow));

	this->addComponent(c1);
	this->addComponent(c2);
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
