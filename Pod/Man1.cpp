#include "Man1.h"

void Man1::viewDidLoad()
{
	ViewController::viewDidLoad();

	// Read data from file
	string dataMario = FileManager::getInstance()->getStringFromTextFile("Mario/mario_info.txt");
	vector<string> vectorMario = Tool::splitToVectorStringFrom(dataMario, ',');
	string dataMap = FileManager::getInstance()->getStringFromTextFile("map_info_man1.txt");
	vector<string> vectorMap = Tool::splitToVectorStringFrom(dataMap, ',');

	map = new Map(L"./Assets/Images/tile_set_man1.png", "map_indexes_man1.txt", "map_info_man1.txt", ' ', NULL);
	mainCharacter = new Mario(stoi(vectorMario[0]), stoi(vectorMario[1]), stoi(vectorMario[2]), stoi(vectorMario[3]), stoi(vectorMap[4]), stoi(vectorMap[5]), L"./Assets/Images/Mario/mario.png", D3DCOLOR_XRGB(255, 255, 255), STANDING_RIGHT);
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	ViewController::viewReceiveKeyDown(_keyType);
}

void Man1::viewReceiveKeyUp()
{
	ViewController::viewReceiveKeyUp();
}
