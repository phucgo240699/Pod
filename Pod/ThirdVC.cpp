#include "ThirdVC.h"

Mario* ThirdVC::getMario()
{
    return this->mario;
}

void ThirdVC::setMario(Mario* _mario)
{
    this->mario = _mario;
}

void ThirdVC::viewDidLoad()
{
    mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
    map = new Map(ImagePath::getInstance()->third_map, D3DCOLOR_XRGB(255, 0, 255));
    sunnyMapTexture = LoadTextureFromImage(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
    grounds = new vector<Ground*>();


	this->mario->load();

	this->adaptData();
	this->adaptAnimation();
}

void ThirdVC::viewReceiveKeyUp()
{
    mario->onKeyUp();
}

void ThirdVC::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
    mario->onKeyUp(_keyTypes);
}

void ThirdVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
    mario->onKeyDown(_keyTypes);
}

void ThirdVC::viewWillUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}
	
	
	//unordered_set<Component*> cell;
	//// Check by cell in grid
	//int beginRow = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	//int endRow = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	//int beginCol = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	//int endCol = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	//for (int i = beginRow; i < endRow; ++i) {
	//	for (int j = beginCol; j < endCol; ++j) {

	//	if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

	//		cell = Grid::getInstance()->getCell(i, j);
	//		if (cell.size() <= 0) continue;

	//		unordered_set<Component*> ::iterator itr;
	//		for (itr = cell.begin(); itr != cell.end(); ++itr) {


	//		}
	//	}
	//}


	if (mario != NULL) {
		mario->Update(_dt);

		// Navigate to WorldVC when Mario drop out of map to far
		if (this->mario->getY() >= Camera::getInstance()->getLimitY() + 100) {
			this->mario->setIsSuperMode(false);
			this->mario->setIsFlyingMode(false);
			this->mario->setIsPreFlyingUpMode(false);
			this->mario->setIsFlyingUpMode(false);

			ScoreBoard::getInstance()->minusMarioLife();

			this->navigateTo(SceneName::WorldScene);
			return;
		}

		Camera::getInstance()->follow(mario, _dt);
	}

	AnimationCDPlayer::getInstance()->Update(_dt);

	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getState() == DROPPING_DOWN_PIPE
		|| this->mario->getState() == POPPING_UP_PIPE
		|| this->mario->getState() == JUMPING_UP_TO_CLOUND
		|| this->mario->getState() == DROPPING_DOWN_WIN
		|| this->mario->getState() == MOVING_RIGHT_WIN) {
		return;
	}
	ScoreBoard::getInstance()->Update(_dt);
	ScoreBoard::getInstance()->setMomentumLevel(this->mario->getMomentumLevelToFly());
}

void ThirdVC::viewDidUpdate(float _dt)
{
	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getState() == TRANSFERING_TO_FLY
		|| this->mario->getState() == DROPPING_DOWN_PIPE
		|| this->mario->getState() == POPPING_UP_PIPE
		|| this->mario->getState() == JUMPING_UP_TO_CLOUND
		|| this->mario->getState() == DROPPING_DOWN_WIN
		|| this->mario->getState() == MOVING_RIGHT_WIN)
	{
		return;
	}

	if (this->mario->getIsStandOnSurface() == true) {
		this->mario->setIsStandOnSurface(false);
	}

	// Check by cell in grid
	unordered_set<Component*> marioCell;
	int beginRowMario = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	int endRowMario = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	int beginColMario = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	int endColMario = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	for (int i = beginRowMario; i < endRowMario; ++i) {
		for (int j = beginColMario; j < endColMario; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			marioCell = Grid::getInstance()->getCell(i, j);
			if (marioCell.size() <= 0) continue;

			unordered_set<Component*> ::iterator itr; // mario to others
			for (itr = marioCell.begin(); itr != marioCell.end(); ++itr) {
				// Ground
				if (beginGroundId <= (*itr)->getId() && (*itr)->getId() <= endGroundId) {
					this->mario->handleGroundCollision(static_cast<Ground*>(*itr), _dt);
				}
			}
		}
	}

	if ((mario->getState() == WALKING || mario->getState() == STANDING) && this->mario->getIsTurningAround() == false && this->mario->getIsStandOnSurface() == false) {
		this->mario->setState(MarioState::DROPPING);
	}
}

void ThirdVC::viewWillRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}

		/*unordered_set<Component*> cell;
		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				cell = Grid::getInstance()->getCell(i, j);
				if (cell.size() <= 0) continue;

				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {
					
				}
			}
		}*/


		if (mario != NULL) {
			mario->Draw();
		}

		AnimationCDPlayer::getInstance()->Draw(sunnyMapTexture);

		ScoreBoard::getInstance()->Draw();

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void ThirdVC::viewDidRender()
{
}

void ThirdVC::viewWillRelease()
{
}

void ThirdVC::adaptRangeID(vector<string> data, char seperator)
{
	vector<int> v;
	for (int i = 0; i < data.size(); ++i) {
		if (i == 0) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGroundId = v[0];
			this->endGroundId = v[1];
		}
	}
}

void ThirdVC::adaptData()
{
	fstream fs;
	fs.open(FilePath::getInstance()->third_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;


	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<ViewController>") {
			section = SECTION_VIEW_CONTROLLER;
			continue;
		}
		else if (line == "</ViewController>") {
			this->adaptRangeID(data, ',');
			section = SECTION_NONE;
		}
		//else if (line == "<Camera>") {
		//	section = SECTION_CAMERA;
		//	continue;
		//}
		//else if (line == "</Camera>") {
		//	section = SECTION_NONE;
		//}
		else if (line == "<MapInfo>") {
			section = SECTION_MAP_INFO;
			continue;
		}
		else if (line == "</MapInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<MapIndexes>") {
			section = SECTION_MAP_INDEXES;
			continue;
		}
		else if (line == "</MapIndexes>") {
			map->loadIndexes(data, ' ');
			section = SECTION_NONE;
		}
		else if (line == "<MarioInfo>") {
			section = SECTION_MARIO_INFO;
			continue;
		}
		else if (line == "</MarioInfo>") {
			section = SECTION_NONE;
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
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_NONE:
			data.clear();
			break;
		case SECTION_VIEW_CONTROLLER:
			data.push_back(line);
			break;
			//case SECTION_CAMERA:
			//	camera->load(line, ',');
			//	break;
		case SECTION_MAP_INFO:
			map->loadInfo(line, ',');
			break;
		case SECTION_MAP_INDEXES:
			data.push_back(line);
			break;
		case SECTION_MARIO_INFO:
			mario->loadInfo(line, ',');
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

void ThirdVC::adaptAnimation()
{
	this->mario->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
	this->mario->setState(MarioState::DROPPING);
	this->mario->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
	this->mario->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
}

void ThirdVC::adaptToGrid()
{
	// Grounds
	for (int i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}
}
