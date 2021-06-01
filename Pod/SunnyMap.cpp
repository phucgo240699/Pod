#include "SunnyMap.h"

void SunnyMap::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, ImagePath::getInstance()->debug_box, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new Map(ImagePath::getInstance()->tile_set_man1, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();

	this->adaptData();
}

void SunnyMap::viewReceiveKeyUp()
{
	mario->onKeyUp();
}

void SunnyMap::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	mario->onKeyUp(_keyTypes);
}

void SunnyMap::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	mario->onKeyDown(_keyTypes);
}

void SunnyMap::viewWillUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}
	if (mario != NULL) {
		mario->Update(_dt);
		Camera::getInstance()->follow(mario, _dt);
	}
}

void SunnyMap::viewDidUpdate(float _dt)
{
	// Collision: MainCharacter and Ground
	for (int i = 0; i < this->grounds->size(); ++i) {
		
			mario_ground_collision = this->mario->sweptAABB(this->grounds->at(i), _dt);
			if (get<0>(mario_ground_collision) == true) {
				for (int j = 0; j < get<2>(mario_ground_collision).size(); ++j) {
					CollisionEdge edge = get<2>(mario_ground_collision)[j];
					if (edge == topEdge) {
						currentGroundIndex = i;
						mario->setState(MarioState::STANDING);
						mario->setY(this->grounds->at(i)->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
					}
					else if (edge == bottomEdge) {
						currentGroundIndex = i;
						mario->setState(MarioState::STANDING);
						mario->setY(this->grounds->at(i)->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
					}
					else if (edge == leftEdge) {
						mario->setSubState(MarioSubState::PUSHING);
					}
					else if (edge == rightEdge) {
						mario->setSubState(MarioSubState::PUSHING);
					}
				}
			}
			else {
				// if mario walk out of ground top surface, it will drop
				if (mario->getState() == WALKING || mario->getState() == STANDING) {
					if (mario->getBounds()->right < this->grounds->at(currentGroundIndex)->getX() || mario->getX() > this->grounds->at(currentGroundIndex)->getBounds()->right) { // this is check which ground that mario is standing on
						if (mario->getBounds()->bottom <= this->grounds->at(currentGroundIndex)->getY()) {
							mario->setState(MarioState::DROPPING);
						}
					}
				}
			}
		
	}
}

void SunnyMap::viewWillRender()
{
}

void SunnyMap::viewDidRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}
		if (mario != NULL) {
			mario->Draw();
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void SunnyMap::viewWillRelease()
{
}

SunnyMap::~SunnyMap()
{
}

void SunnyMap::adaptData()
{
	Camera* camera = Camera::getInstance();
	Setting* setting = Setting::getInstance();

	fstream fs;
	fs.open(FilePath::getInstance()->sunny_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;


	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<Setting>") {
			section = SECTION_SETTING;
			continue;
		}
		else if (line == "</Setting>") {
			section = SECTION_NONE;
			continue;
		}
		else if (line == "<Camera>") {
			section = SECTION_CAMERA;
			continue;
		}
		else if (line == "</Camera>") {
			section = SECTION_NONE;
			continue;
		}
		else if (line == "<MapInfo>") {
			section = SECTION_MAP_INFO;
			continue;
		}
		else if (line == "</MapInfo>") {
			section = SECTION_NONE;
			continue;
		}
		else if (line == "<MapIndexes>") {
			section = SECTION_MAP_INDEXES;
			continue;
		}
		else if (line == "</MapIndexes>") {
			map->loadIndexes(data, ' ');
			data.clear();
			section = SECTION_NONE;
			continue;
		}
		else if (line == "<MarioInfo>") {
			section = SECTION_MARIO_INFO;
			continue;
		}
		else if (line == "</MarioInfo>") {
			section = SECTION_NONE;
			continue;
		}
		else if (line == "<MarioAnimations>") {
			section = SECTION_MARIO_ANIMATIONS;
			continue;
		}
		else if (line == "</MarioAnimations>") {
			mario->loadAnimations(data, '>', ',');
			data.clear();
			continue;
		}
		else if (line == "<Grounds>") {
			section = SECTION_GROUNDS;
			continue;
		}
		else if (line == "</Grounds>") {
			for (int i = 0; i < data.size(); ++i) {
				Ground* ground = new Ground(0, 0, 0, 0, 0, 0, 0, 0);
				ground->load(data[i], ',');
				this->grounds->push_back(ground);
			}
			data.clear();
			section = SECTION_NONE;
			continue;
		}

		switch (section)
		{
		case SECTION_NONE:
			break;
		case SECTION_SETTING:
			setting->load(line, ',');
			break;
		case SECTION_CAMERA:
			camera->load(line, ',');
			break;
		case SECTION_MAP_INFO:
			map->loadInfo(line, ',');
			break;
		case SECTION_MAP_INDEXES:
			data.push_back(line);
			break;
		case SECTION_MARIO_INFO:
			mario->loadInfo(line, ',');
			break;
		case SECTION_MARIO_ANIMATIONS:
			data.push_back(line);
			break;
		case SECTION_GROUNDS:
			data.push_back(line);
			break;
		default:
			break;
		}
	}

	fs.close();
}
