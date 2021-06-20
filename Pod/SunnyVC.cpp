#include "SunnyVC.h"

void SunnyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new SunnyMap(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();
	goldenBricks = new vector<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();

	this->adaptData();
	this->adaptAnimationBundle();
	this->adaptToGrid();
}

void SunnyVC::viewReceiveKeyUp()
{
	mario->onKeyUp();
}

void SunnyVC::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	mario->onKeyUp(_keyTypes);
}

void SunnyVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	mario->onKeyDown(_keyTypes);
}

void SunnyVC::viewWillUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}

	// Check by cell in grid	
	for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
		for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			for (int k = 0; k < Grid::getInstance()->getCell(i, j).size(); ++k) {
				if (beginGoldenBrickId <= Grid::getInstance()->getCell(i, j)[k]->getId() && Grid::getInstance()->getCell(i, j)[k]->getId() <= endGiftBrickId) {
					Grid::getInstance()->getCell(i, j)[k]->Update(_dt);
				}
			}
		}
	}

	ScoreBoard::getInstance()->Update(_dt);

	if (mario != NULL) {
		mario->Update(_dt);
		Camera::getInstance()->follow(mario, _dt);
	}
}

void SunnyVC::viewDidUpdate(float _dt)
{

	// Check by cell in grid

	if (this->mario->getIsStandOnSurface() == true) {
		this->mario->setIsStandOnSurface(false);
	}

	for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
		for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			for (int k = 0; k < Grid::getInstance()->getCell(i, j).size(); ++k) {
				if (beginGroundId <= Grid::getInstance()->getCell(i, j)[k]->getId() && Grid::getInstance()->getCell(i, j)[k]->getId() <= endGroundId) {
					this->handleMarioGroundCollision(Grid::getInstance()->getCell(i, j)[k], _dt);
				}
				else if (beginGoldenBrickId <= Grid::getInstance()->getCell(i, j)[k]->getId() && Grid::getInstance()->getCell(i, j)[k]->getId() <= endGoldenBrickId) {
					this->handleMarioGoldenBrickCollision(Grid::getInstance()->getCell(i, j)[k], _dt);
				}
				else if (beginGiftBrickId <= Grid::getInstance()->getCell(i, j)[k]->getId() && Grid::getInstance()->getCell(i, j)[k]->getId() <= endGiftBrickId) {
					this->handleMarioGiftBrickCollision(static_cast<GiftBrick*>(Grid::getInstance()->getCell(i, j)[k]), _dt);
					//static_cast<GiftBrick*>(Grid::getInstance()->getCell(i, j)[k])->setState(GiftBrickState::EMPTY);
				}
			}
		}
	}

	if ((mario->getState() == WALKING || mario->getState() == STANDING) && this->mario->getIsStandOnSurface() == false) {
		this->mario->setState(MarioState::DROPPING);
	}
}

void SunnyVC::viewWillRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}

		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				for (int k = 0; k < Grid::getInstance()->getCell(i, j).size(); ++k) {
					if (beginGoldenBrickId <= Grid::getInstance()->getCell(i, j)[k]->getId() && Grid::getInstance()->getCell(i, j)[k]->getId() <= endGiftBrickId) {
						Grid::getInstance()->getCell(i, j)[k]->Draw(map->getTexture());
					}
				}
			}
		}

		if (mario != NULL) {
			mario->Draw();
		}

		ScoreBoard::getInstance()->Draw();

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void SunnyVC::viewDidRender()
{
}

void SunnyVC::viewWillRelease()
{
}

void SunnyVC::handleMarioGroundCollision(Component* _ground, float _dt)
{
	mario_ground_collision = this->mario->sweptAABB(_ground, _dt);
	if (get<0>(mario_ground_collision) == true) {
		for (int j = 0; j < get<2>(mario_ground_collision).size(); ++j) {
			CollisionEdge edge = get<2>(mario_ground_collision)[j];
			if (edge == topEdge) {
				mario->setState(MarioState::DROPPING);
				mario->setY(_ground->getBounds().bottom);
				mario->setVy(0);
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _ground->getId();
			}
			else if (edge == bottomEdge) {
				mario->setState(MarioState::STANDING);
				mario->setY(_ground->getY() - mario->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _ground->getId();
			}
			else if (edge == leftEdge) {
				mario->setX(_ground->getBounds().right + Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				mario->setX(_ground->getBounds().left - mario->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (mario->getState() == WALKING || mario->getState() == STANDING) {
			if (mario->getIsStandOnSurface() == false) {
				if ((_ground->getX() <= mario->getBounds().right && mario->getBounds().right <= _ground->getBounds().right)
					|| (_ground->getX() <= mario->getX() && mario->getX() <= _ground->getBounds().right)) { // this is check which ground that mario is standing on
					if (mario->getBounds().bottom == _ground->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						mario->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void SunnyVC::handleMarioGoldenBrickCollision(Component* _goldenBrick, float _dt)
{
	tuple<bool, float, vector<CollisionEdge>> mario_golden_brick_collision = this->mario->sweptAABB(_goldenBrick, _dt);
	if (get<0>(mario_golden_brick_collision) == true) {
		for (int j = 0; j < get<2>(mario_golden_brick_collision).size(); ++j) {
			CollisionEdge edge = get<2>(mario_golden_brick_collision)[j];
			if (edge == topEdge) {
				mario->setState(MarioState::DROPPING);
				mario->setY(_goldenBrick->getBounds().bottom);
				mario->setVy(0);
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == bottomEdge) {
				mario->setState(MarioState::STANDING);
				mario->setY(_goldenBrick->getY() - mario->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == leftEdge) {
				mario->setX(_goldenBrick->getBounds().right + Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				mario->setX(_goldenBrick->getBounds().left - mario->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (mario->getState() == WALKING || mario->getState() == STANDING) {
			if (mario->getIsStandOnSurface() == false) {
				if ((_goldenBrick->getX() <= mario->getBounds().right && mario->getBounds().right <= _goldenBrick->getBounds().right)
					|| (_goldenBrick->getX() <= mario->getX() && mario->getX() <= _goldenBrick->getBounds().right)) { // this is check which ground that mario is standing on
					if (mario->getBounds().bottom == _goldenBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						mario->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void SunnyVC::handleMarioGiftBrickCollision(GiftBrick* _goldenBrick, float _dt)
{
	mario_ground_collision = this->mario->sweptAABB(_goldenBrick, _dt);
	if (get<0>(mario_ground_collision) == true) {
		for (int j = 0; j < get<2>(mario_ground_collision).size(); ++j) {
			CollisionEdge edge = get<2>(mario_ground_collision)[j];
			if (edge == topEdge) {
				mario->setState(MarioState::DROPPING);
				mario->setY(_goldenBrick->getBounds().bottom);
				mario->setVy(0);
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _goldenBrick->getId();
				if (_goldenBrick->getState() == FULLGIFTBRICK) {
					_goldenBrick->setState(GiftBrickState::POPUPGIFTBRICK);
					if (_goldenBrick->getGiftId() == 1) {
						ScoreBoard::getInstance()->plusCoin(1);
						ScoreBoard::getInstance()->plusPoint(100);
					}
				}
			}
			else if (edge == bottomEdge) {
				mario->setState(MarioState::STANDING);
				mario->setY(_goldenBrick->getY() - mario->getHeight() - Setting::getInstance()->getCollisionSafeSpace());
				this->mario->setIsStandOnSurface(true);
				this->componentIdStanded = _goldenBrick->getId();
			}
			else if (edge == leftEdge) {
				mario->setX(_goldenBrick->getBounds().right + Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				mario->setX(_goldenBrick->getBounds().left - mario->getWidth() - Setting::getInstance()->getCollisionSafeSpace());
				mario->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	else {
		// if mario walk out of ground's top surface, it will drop
		if (mario->getState() == WALKING || mario->getState() == STANDING) {
			if (mario->getIsStandOnSurface() == false) {
				if ((_goldenBrick->getX() <= mario->getBounds().right && mario->getBounds().right <= _goldenBrick->getBounds().right)
					|| (_goldenBrick->getX() <= mario->getX() && mario->getX() <= _goldenBrick->getBounds().right)) { // this is check which ground that mario is standing on
					if (mario->getBounds().bottom == _goldenBrick->getY() - Setting::getInstance()->getCollisionSafeSpace()) {
						mario->setIsStandOnSurface(true);
					}
				}
			}
		}
	}
}

void SunnyVC::adaptData()
{
	Camera* camera = Camera::getInstance();

	fstream fs;
	fs.open(FilePath::getInstance()->sunny_map, ios::in);

	SectionFileType section = SECTION_NONE;
	vector<string> data = vector<string>();
	string line;


	while (!fs.eof()) { // End of line
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty

		if (line == "<Camera>") {
			section = SECTION_CAMERA;
			continue;
		}
		else if (line == "</Camera>") {
			section = SECTION_NONE;
		}
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
		else if (line == "<MarioAnimations>") {
			section = SECTION_MARIO_ANIMATIONS;
			continue;
		}
		else if (line == "</MarioAnimations>") {
			mario->loadAnimations(data, '>', ',');
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
			section = SECTION_NONE;
		}
		else if (line == "<GoldenBrickFrames>") {
			section = SECTION_GOLDEN_BRICK_FRAMES;
			continue;
		}
		else if (line == "</GoldenBrickFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				GoldenBrick* goldenBrick = new GoldenBrick(0, 0, 0, 0, 0, 0, 0);
				goldenBrick->loadInfo(data[i], ',');
				this->goldenBricks->push_back(goldenBrick);
			}
			section = SECTION_NONE;
		}
		else if (line == "<GoldenBrickAnimation>") {
			section = SECTION_GOLDEN_BRICK_ANIMATION;
			continue;
		}
		else if (line == "</GoldenBrickAnimation>") {
			for (int i = 0; i < this->goldenBricks->size(); ++i) {
				this->goldenBricks->at(i)->loadAnimation(data, '>', ',');
			}
			section = SECTION_NONE;
		}
		else if (line == "<GiftBrickFrames>") {
			section = SECTION_GIFT_BRICK_FRAMES;
			continue;
		}
		else if (line == "</GiftBrickFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				GiftBrick* giftBrick = new GiftBrick(0, 0, 0, 0, 0, 0);
				giftBrick->loadInfo(data[i], ',');
				giftBricks->push_back(giftBrick);
			}
			section = SECTION_NONE;
		}
		else if (line == "<ScoreBoard>") {
			section = SECTION_SCORE_BOARD;
			continue;
		}
		else if (line == "</ScoreBoard>") {
			section = SECTION_NONE;
		}
		else if (line == "<ScoreBoardFrames>") {
			section = SECTION_sCORE_BOARD_FRAMES;
			continue;
		}
		else if (line == "</ScoreBoardFrames>") {
			ScoreBoard::getInstance()->loadFrames(data, '-', ',');
			section = SECTION_NONE;
		}
		else if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<GridMatrixId>") {
			section = SECTION_GRID_MATRIX_ID;
			continue;
		}
		else if (line == "</GridMatrixId>") {
			Grid::getInstance()->loadMatrixId(data, '>', '_', ',');
			section = SECTION_NONE;
		}
		else if (line == "<AnimationBundle>") {
			section = SECTION_ANIMATION_BUNDLE;
			continue;
		}
		else if (line == "</AnimationBundle>") {
			AnimationBundle::getInstance()->loadAnimations(data, '>', ',');
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_NONE:
			data.clear();
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
		case SECTION_GIFT_BRICK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_SCORE_BOARD:
			ScoreBoard::getInstance()->loadInfo(line, ',');
			break;
		case SECTION_sCORE_BOARD_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GOLDEN_BRICK_ANIMATION:
			data.push_back(line);
			break;
		case SECTION_GOLDEN_BRICK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GRID_INFO:
			Grid::getInstance()->loadInfo(line, ',');
			break;
		case SECTION_GRID_MATRIX_ID:
			data.push_back(line);
		case SECTION_ANIMATION_BUNDLE:
			data.push_back(line);
		default:
			break;
		}
	}

	fs.close();
}

void SunnyVC::adaptAnimationBundle()
{
	/*giftBrick->setState(GiftBrickState::FULL);*/
}

void SunnyVC::adaptToGrid()
{
	// Grounds
	for (int i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}

	// Golden Bricks
	for (int i = 0; i < this->goldenBricks->size(); ++i) {
		Grid::getInstance()->add(this->goldenBricks->at(i));
	}

	// Gift Bricks
	for (int i = 0; i < this->giftBricks->size(); ++i) {
		this->giftBricks->at(i)->setState(GiftBrickState::FULLGIFTBRICK);
		Grid::getInstance()->add(this->giftBricks->at(i));
	}
}
