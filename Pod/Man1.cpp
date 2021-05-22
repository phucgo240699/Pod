#include "Man1.h"

void Man1::viewDidLoad()
{
	ViewController::viewDidLoad();

	// Read data from file
	string dataMario = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->mario_info);
	vector<string> vectorMario = Tool::splitToVectorStringFrom(dataMario, ',');
	string dataMap = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->map_info_man1);
	vector<string> vectorMap = Tool::splitToVectorStringFrom(dataMap, ',');
	string dataGround = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->ground_man1);
	vector<string> vectorGround = Tool::splitToVectorStringFrom(dataGround, ',');

	map = new Map(ImagePath::getInstance()->tile_set_man1, FilePath::getInstance()->map_indexes_man1, FilePath::getInstance()->map_info_man1, ' ', NULL);
	mainCharacter = new Mario(stof(vectorMario[0]), stof(vectorMario[1]), stof(vectorMario[2]), stof(vectorMario[3]), stof(vectorMap[4]), stof(vectorMap[5]), ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), STANDING_RIGHT);
	Camera::getInstance()->setPositionBy(mainCharacter);
	Ground* ground = new Ground(stof(vectorGround[0]), stof(vectorGround[1]), stof(vectorGround[2]), stof(vectorGround[3]), stof(vectorGround[4]), stof(vectorGround[5]), stof(vectorGround[6]), stof(vectorGround[7]));
}

void Man1::viewReceiveKeyDown(KeyType _keyType)
{
	ViewController::viewReceiveKeyDown(_keyType);
}

void Man1::viewReceiveKeyUp()
{
	ViewController::viewReceiveKeyUp();
}
