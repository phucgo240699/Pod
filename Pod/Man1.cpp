#include "Man1.h"

Man1::Man1()
{
	RECT* r1 = new RECT();
	r1->top = 5;
	r1->bottom = r1->top + 100;
	r1->left = 500;
	r1->right = 500 + 500;
	Component* c1 = new Component(r1, new Color(yellow));

	this->addComponent(c1);
}
