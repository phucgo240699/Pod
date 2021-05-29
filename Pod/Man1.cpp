#include "Man1.h"

void Man1::viewDidLoad()
{
	ViewController::viewDidLoad();

	Camera::getInstance()->load();

	// Read data from file
	string dataMario = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->mario_info);
	vector<string> vectorMario = Tool::splitToVectorStringFrom(dataMario, ',');
	string dataMap = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->map_info_man1);
	vector<string> vectorMap = Tool::splitToVectorStringFrom(dataMap, ',');
	string dataGround = FileManager::getInstance()->getStringFromTextFile(FilePath::getInstance()->ground_man1);
	vector<string> vectorGround = Tool::splitToVectorStringFrom(dataGround, ',');

	map = new Map(ImagePath::getInstance()->tile_set_man1, FilePath::getInstance()->map_indexes_man1, FilePath::getInstance()->map_info_man1, ' ', NULL);
	mainCharacter = new Mario(stof(vectorMario[0]), stof(vectorMario[1]), 0, 0, stof(vectorMap[4]), stof(vectorMap[5]), ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	Camera::getInstance()->setPositionBy(mainCharacter);
	ground = new Ground(stof(vectorGround[0]), stof(vectorGround[1]), stof(vectorGround[2]), stof(vectorGround[3]), stof(vectorGround[4]), stof(vectorGround[5]), stof(vectorGround[6]), stof(vectorGround[7]));
}

void Man1::viewReceiveKeyUp()
{
	mainCharacter->onKeyUp();
}

void Man1::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	mainCharacter->onKeyUp(_keyTypes);
}

void Man1::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	mainCharacter->onKeyDown(_keyTypes);
}

void Man1::viewWillUpdate(float _dt)
{
}

void Man1::viewDidUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}
	if (mainCharacter != NULL) {
		mainCharacter->Update(_dt);
		Camera::getInstance()->follow(mainCharacter, _dt);
	}

	// Collision: MainCharacter and Ground
	tuple<bool, float, vector<CollisionEdge>> mainCharacter_ground_collision = this->mainCharacter->sweptAABB(this->ground, _dt);
	if (get<0>(mainCharacter_ground_collision) == true) {
		(mainCharacter->setState(MarioState::STANDING));
		for (int i = 0; i < get<2>(mainCharacter_ground_collision).size(); ++i) {
			CollisionEdge edge = get<2>(mainCharacter_ground_collision)[i];
			if (edge == topEdge) {
				mainCharacter->setY(ground->getY() - (mainCharacter->getCurrentAnimation()->getCurrentFrameHeight()));
			}
		}
	}
}

void Man1::viewWillRender()
{
}

void Man1::viewDidRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}
		if (mainCharacter != NULL) {
			mainCharacter->Draw();
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Man1::viewWillRelease()
{
}
