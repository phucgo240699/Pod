#include "Man1.h"

void Man1::viewDidLoad()
{
	ViewController::viewDidLoad();

	// Read data from file
	string dataMario = FileManager::getInstance()->getStringFromTextFile("mario.txt");
	vector<string> vectorMario = Tool::splitToVectorStringFrom(dataMario, ',');
	string dataMap = FileManager::getInstance()->getStringFromTextFile("map_info_man1.txt");
	vector<string> vectorMap = Tool::splitToVectorStringFrom(dataMap, ',');

	map = new Map(L"./Assets/Images/tile_set_man1.png", "map_indexes_man1.txt", "map_info_man1.txt", ' ', NULL);
	mainCharacter = new Mario(stoi(vectorMario[0]), stoi(vectorMario[1]), stoi(vectorMario[2]), stoi(vectorMario[3]), stoi(vectorMap[4]), stoi(vectorMap[5]), L"./Assets/Images/mario.png", NULL, STANDING);
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
