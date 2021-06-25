#include "SunnyVC.h"

void SunnyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new SunnyMap(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();
	goldenBricks = new vector<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();
	greenPipes = new vector<GreenPipe*>();
	goombas = new unordered_set<Goomba*>();
	blocks = new vector<Block*>();

	this->adaptData();
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

			unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			unordered_set<Component*> ::iterator itr;
			for (itr = cell.begin(); itr != cell.end(); ++itr) {
				if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					(*itr)->Update(_dt);
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
	int x = this->mario->getX();
	int y = this->mario->getY();

	if (this->mario->getIsStandOnSurface() == true) {
		this->mario->setIsStandOnSurface(false);
	}

	for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
		for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			unordered_set<Component*> ::iterator itr; // mario to others
			unordered_set<Component*> ::iterator itr2; // goomba to others

			for (itr = cell.begin(); itr != cell.end(); ++itr) {
				if (beginGroundId <= (*itr)->getId() && (*itr)->getId() <= endGroundId) {
					this->mario->handleGroundCollision(static_cast<Ground*>(*itr), _dt);
				}
				if (beginBlockId <= (*itr)->getId() && (*itr)->getId() <= endBlockId) {
					this->mario->handleBlockCollision(static_cast<Block*>(*itr), _dt);
				}
				else if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					this->mario->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*itr), _dt);
				}
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					this->mario->handleGiftBrickCollision(static_cast<GiftBrick*>(*itr), _dt);
				}
				else if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
					this->mario->handleGreenPipeCollision(static_cast<GreenPipe*>(*itr), _dt);
				}
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					if (static_cast<Goomba*>(*itr)->getState() == DEAD_GOOMBA) {
						Grid::getInstance()->remove(*itr, i, j);
						this->goombas->erase(static_cast<Goomba*>(*itr));
						return;
					}
					this->mario->handleGoombaCollision(static_cast<Goomba*>(*itr), _dt);
					for (itr2 = cell.begin(); itr2 != cell.end(); ++itr2) {
						if ((beginGroundId <= (*itr2)->getId() && (*itr2)->getId() <= endGroundId)
							|| (beginGoldenBrickId <= (*itr2)->getId() && (*itr2)->getId() <= endGoldenBrickId)) {
							static_cast<Goomba*>(*itr)->handleGroundCollision((*itr2), _dt);
						}
					}
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

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {
					if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
						(*itr)->Draw(map->getTexture());
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
		else if (line == "<BlockFrames>") {
			section = SECTION_BLOCK_FRAMES;
			continue;
		}
		else if (line == "</BlockFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				Block* block = new Block(0, 0, 0, 0, 0, 0, 0, 0);
				block->load(data[i], ',');
				blocks->push_back(block);
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
		else if (line == "<GoombaFrames>") {
			section = SECTION_GOOMBA_FRAMES;
			continue;
		}
		else if (line == "</GoombaFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				Goomba* goomba = new Goomba(0, 0, 0, 0, 0, 0, 0);
				goomba->loadInfo(data[i], ',');
				goombas->insert(goomba);
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
		case SECTION_BLOCK_FRAMES:
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
		case SECTION_GREEN_PIPE_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GOOMBA_FRAMES:
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

void SunnyVC::adaptToGrid()
{
	// Grounds
	for (int i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}

	// Blocks
	for (int i = 0; i < this->blocks->size(); ++i) {
		Grid::getInstance()->add(this->blocks->at(i));
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

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		this->greenPipes->at(i)->setup();
		Grid::getInstance()->add(this->greenPipes->at(i));
	}

	///
	/// Enemies
	///

	// Goombas
	unordered_set<Goomba*> ::iterator itr;
	for (itr = this->goombas->begin(); itr != this->goombas->end(); ++itr) {
		(*itr)->setState(GoombaState::GOOMBA_MOVING);
		Grid::getInstance()->add(*itr);
	}
}
