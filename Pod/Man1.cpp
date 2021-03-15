#include "Man1.h"

Man1::Man1()
{
	RECT* r1 = new RECT();
	r1->top = 300;
	r1->bottom = r1->top + 100;
	r1->left = 200;
	r1->right = r1->left + 500;
	RECT* r2 = new RECT();
	r2->top = 0;
	r2->bottom = r2->top + 100;
	r2->left = 0;
	r2->right = r2->left + 500;
	c1 = new Component(r1, new Color(yellow));
	c2 = new Component(r2, new Color(yellow));

	this->addComponent(c1);
	this->addComponent(c2);
}
