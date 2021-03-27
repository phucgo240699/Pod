#include "Man1.h"

void Man1::viewDidLoad()
{
	mainCharacter = new Mario(100, 100, L"./Assets/Images/mario.png", NULL, STANDING);
	this->addComponent(mainCharacter);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	mainCharacter->onKeyDown(_keyType);
}

void Man1::viewReceiveKeyUp()
{
	mainCharacter->onKeyUp();
}
