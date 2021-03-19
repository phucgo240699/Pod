#include "Man1.h"

void Man1::viewDidLoad()
{
	mainCharacter = new Mario(100, 100, L"./Assets/Images/mario.png", NULL, STANDING);
	this->addComponent(mainCharacter);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	/*switch (_keyType)
	{
	case KeyType::left:
		mainCharacter->setState(WALKING_LEFT);
	case KeyType::right:
		mainCharacter->setState(WALKING_RIGHT);
	}*/
}

void Man1::viewReceiveKeyUp(KeyType _keyType)
{
	/*switch (_keyType)
	{
	case KeyType::left:
		mainCharacter->setState(STANDING);
		break;
	case KeyType::right:
		mainCharacter->setState(STANDING);
		break;
	}*/
}
