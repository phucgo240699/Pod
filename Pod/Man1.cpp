#include "Man1.h"

void Man1::viewDidLoad()
{
	ViewController::viewDidLoad();

	//// Read data from file
	//string data = FileManager::getInstance()->getStringFromTextFile("mario.txt");
	//vector<string> v = Tool::splitToVectorStringFrom(data, ',');

	map = new Map(L"./Assets/Images/tile_set_man1.png", "map_indexes_man1.txt", "map_info_man1.txt", ' ', NULL);
	//mainCharacter = new Mario(stoi(v[0]), stoi(v[1]), stoi(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5]), stoi(v[6]), L"./Assets/Images/mario.png", NULL, STANDING);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	ViewController::viewReceiveKeyDown(_keyType);
	//mainCharacter->onKeyDown(_keyType);


	Camera* camera = Camera::getInstance();
	if (_keyType == KeyType::up) {
		if (camera->getY() >= 1) {
			camera->plusY(-1);
		}
	}
	if (_keyType == KeyType::down) {
		if (camera->getY() + camera->getHeight() <= camera->getLimitY() - 1) {
			camera->plusY(1);
		}
	}
	if (_keyType == KeyType::left) {
		if (camera->getX() >= 1) {
			camera->plusX(-1);
		}
	}
	if (_keyType == KeyType::right) {
		if (camera->getX() + camera->getWidth() <= camera->getLimitX() - 1) {
			camera->plusX(1);
		}
	}
}

void Man1::viewReceiveKeyUp()
{
	ViewController::viewReceiveKeyUp();
	//mainCharacter->onKeyUp();
}
