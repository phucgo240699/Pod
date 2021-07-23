#include "CloudyVC.h"

Mario* CloudyVC::getMario()
{
    return this->mario;
}

void CloudyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new Map();
	grounds = new vector<Ground*>();
	coins = new unordered_set<Coin*>();
	greenPipes = new vector<GreenPipe*>();

	this->mario->load();

	this->adaptData();
	this->adaptAnimation();
}

void CloudyVC::viewReceiveKeyUp()
{
	mario->onKeyUp();
}

void CloudyVC::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	mario->onKeyUp(_keyTypes);
}

void CloudyVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	mario->onKeyDown(_keyTypes);
}

void CloudyVC::viewWillUpdate(float _dt)
{// Check by cell in grid
	int beginRow = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	int endRow = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	int beginCol = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	int endCol = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			unordered_set<Component*> ::iterator itr;
			for (itr = cell.begin(); itr != cell.end(); ++itr) {
				if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY) {
					continue;
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}
			}
		}
	}
}

void CloudyVC::viewUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}

	// Check by cell in grid
	int beginRow = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	int endRow = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	int beginCol = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	int endCol = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			unordered_set<Component*> ::iterator itr;
			for (itr = cell.begin(); itr != cell.end(); ++itr) {
				if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY) {
					continue;
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Coin*>(*itr)->getState() == COIN_BEING_EARNED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					(*itr)->Update(_dt);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<FireBall*>(*itr)->getState() == FIREBALL_DISAPPEARED) {
						Grid::getInstance()->remove(*itr, i, j);
						static_cast<FireBall*>(*itr)->setIsOutOfGrid(true);
						continue;
					}

					(*itr)->Update(_dt);

					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->isCollidingByFrame(Camera::getInstance()->getFrame()) == false) {
						Grid::getInstance()->remove(*itr, i, j);
						static_cast<FireBall*>(*itr)->setIsOutOfGrid(true);
					}
				}
			}
		}
	}

	if (mario != NULL) {
		mario->Update(_dt);

		if (this->mario->getState() == POPPING_UP_PIPE) {
			if (this->mario->getY() <= this->mario->getEndPoppingUpPipe()) {
				this->navigateTo(SceneName::SunnyScene);
				return;
			}
		}
		else {

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
	}

	AnimationCDPlayer::getInstance()->Update(_dt);

	if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN) {
		return;
	}
	ScoreBoard::getInstance()->Update(_dt);
	ScoreBoard::getInstance()->setMomentumLevel(this->mario->getMomentumLevelToFly());
}

void CloudyVC::viewDidUpdate(float _dt)
{
	if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY)
	{
		return;
	}

	if (this->mario->getIsStandOnSurface() == true) {
		this->mario->setIsStandOnSurface(false);
	}

	// Check by cell in grid
	int beginRowMario = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	int endRowMario = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	int beginColMario = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	int endColMario = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	for (int i = beginRowMario; i < endRowMario; ++i) {
		for (int j = beginColMario; j < endColMario; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			unordered_set<Component*> marioCell = Grid::getInstance()->getCell(i, j);
			unordered_set<Component*> ::iterator itr; // mario to others

			for (itr = marioCell.begin(); itr != marioCell.end(); ++itr) {
				// Ground
				if (beginGroundId <= (*itr)->getId() && (*itr)->getId() <= endGroundId) {
					this->mario->handleGroundCollision(static_cast<Ground*>(*itr), _dt);
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					this->mario->handleCoinCollision(static_cast<Coin*>(*itr), _dt);
					static_cast<Coin*>(*itr)->handleMarioCollision(this->mario, _dt);
				}

				// Green Pipe
				else if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
					this->mario->handleGreenPipeDownCollision(static_cast<GreenPipe*>(*itr), this->greenPipeIdToThirdMap, this->leftAnchorGreenPipeToPassThrough, this->rightAnchorGreenPipeToPassThrough, _dt);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// FireBall to others
					int beginRowFireball = floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int endRowFireball = ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int beginColFireball = floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());
					int endColFireball = ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());

					beginRowFireball = beginRowFireball < 0 ? 0 : beginRowFireball;
					endRowFireball = endRowFireball > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowFireball;
					beginColFireball = beginColFireball < 0 ? 0 : beginColFireball;
					endColFireball = endColFireball > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColFireball;

					unordered_set<Component*> fireBallCell;
					for (int r = beginRowFireball; r < endRowFireball; ++r) {
						for (int c = beginColFireball; c < endColFireball; ++c) {
							fireBallCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator fireBallItr;

							for (fireBallItr = fireBallCell.begin(); fireBallItr != fireBallCell.end(); ++fireBallItr) {
								if ((beginGroundId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGroundId)
									|| (beginGreenPipeId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGreenPipeId)) {
									static_cast<FireBall*>(*itr)->handleHardComponentCollision(*fireBallItr, _dt);
								}
							}
						}
					}
				}
			}
		}
	}

	if ((mario->getState() == WALKING || mario->getState() == STANDING) && this->mario->getIsTurningAround() == false && this->mario->getIsStandOnSurface() == false) {
		this->mario->setState(MarioState::DROPPING);
	}
}

void CloudyVC::viewWillRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw(Drawing::getInstance()->getCloudyMapTexture());
		}

		unordered_set<Component*> cell;
		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {

					// Coin
					if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}
				}
			}
		}

		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {

					// Fire Ball
					if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}
				}
			}
		}

		if (mario != NULL) {
			mario->Draw();
		}

		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {
					// Green Pipe
					if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
						(*itr)->Draw(Drawing::getInstance()->getUndergroundMapTexture());
					}
				}
			}
		}

		AnimationCDPlayer::getInstance()->Draw(Drawing::getInstance()->getSunnyMapTexture());

		ScoreBoard::getInstance()->Draw();

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CloudyVC::viewDidRender()
{
}

void CloudyVC::viewWillRelease()
{
}

void CloudyVC::adaptRangeID(vector<string> data, char seperator)
{
	vector<int> v;
	for (int i = 0; i < data.size(); ++i) {
		if (i == 0) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGroundId = v[0];
			this->endGroundId = v[1];
		}
		else if (i == 1) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginCoinId = v[0];
			this->endCoinId = v[1];
		}
		else if (i == 2) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGreenPipeId = v[0];
			this->endGreenPipeId = v[1];
			this->greenPipeIdToThirdMap = v[2];
			this->leftAnchorGreenPipeToPassThrough = v[3];
			this->rightAnchorGreenPipeToPassThrough = v[4];
		}
		else if (i == 3) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginFireBallId = v[0];
			this->endFireBallId = v[1];
		}

	}
}

void CloudyVC::adaptData()
{
	fstream fs;
	fs.open(FilePath::getInstance()->cloudy_map, ios::in);

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
		else if (line == "<CoinFrames>") {
			section = SECTION_COIN_FRAMES;
			continue;
		}
		else if (line == "</CoinFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				Coin* coin = new Coin(0, 0, 0, 0, 0, 0, 0, 0);
				coin->loadInfo(data[i], ',');
				this->coins->insert(coin);
			}
			section = SECTION_NONE;
		}
		else if (line == "<GreenPipeFrames>") {
			section = SECTION_GREEN_PIPE_FRAMES;
			continue;
		}
		else if (line == "</GreenPipeFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				GreenPipe* greenPipe = new GreenPipe(0, 0, 0, 0, 0, 0, 0);
				greenPipe->loadInfo(data[i], ',');
				greenPipes->push_back(greenPipe);
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
		case SECTION_COIN_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GREEN_PIPE_FRAMES:
			data.push_back(line);
			break;
		default:
			break;

		}
	}

	fs.close();
}

void CloudyVC::adaptAnimation()
{
	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		(*coinItr)->setAnimation(new Animation(AnimationBundle::getInstance()->getCoin()));
	}

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		this->greenPipes->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getBlackPipe2FloorDown()));
	}

	this->mario->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
	this->mario->setState(MarioState::DROPPING);
	this->mario->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
	this->mario->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
}

void CloudyVC::adaptToGrid()
{
	// Grounds
	for (int i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}

	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		Grid::getInstance()->add(*coinItr);
	}

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		Grid::getInstance()->add(this->greenPipes->at(i));
	}
}
