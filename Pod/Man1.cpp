#include "Man1.h"

void Man1::viewDidLoad()
{

	c1 = new View(50, 50, 100, 100, D3DCOLOR_XRGB(255, 0, 0));

	this->addComponent(c1);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{

}
