#include "SunnyVC.h"

SunnyVC::~SunnyVC()
{
	delete mario;
	delete map;

	// Ground
	for (int i = 0; i < this->grounds->size(); ++i) {
		delete this->grounds->at(i);
	}
	delete this->grounds;

	// Block
	for (int i = 0; i < this->blocks->size(); ++i) {
		delete this->blocks->at(i);
	}
	delete this->blocks;
	
	// Golden Brick
	for (int i = 0; i < this->goldenBricks->size(); ++i) {
		delete this->goldenBricks->at(i);
	}
	delete this->goldenBricks;

	// Gift Brick
	for (int i = 0; i < this->giftBricks->size(); ++i) {
		delete this->giftBricks->at(i);
	}
	delete this->giftBricks;

	// Green Pipe
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		delete this->greenPipes->at(i);
	}
	delete this->greenPipes;

	// Goomba
	unordered_set<Goomba*> ::iterator itr;
	for (itr = this->goombas->begin(); itr != this->goombas->end(); ++itr) {
		delete (*itr);
	}
	delete this->goombas;
}

void SunnyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new SunnyMap(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();
	goldenBricks = new vector<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();
	greenPipes = new vector<GreenPipe*>();
	goombas = new unordered_set<Goomba*>();
	koopas = new unordered_set<Koopa*>();
	blocks = new vector<Block*>();

	ScoreBoard::getInstance()->resetTimeTo300();

	this->adaptData();
	this->adaptAnimation();
	this->adaptToGrid();
}

void SunnyVC::viewReceiveKeyUp()
{
	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN) {
		return;
	}
	mario->onKeyUp();
}

void SunnyVC::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN) {
		return;
	}
	mario->onKeyUp(_keyTypes);
}

void SunnyVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN) {
		return;
	}
	mario->onKeyDown(_keyTypes);
}

void SunnyVC::viewWillUpdate(float _dt)
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
				// Gift Brick
				if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP) {
					/*if ((*itr)->getId() < beginGiftBrickId || (*itr)->getId() > endGiftBrickId) continue;*/
					if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
						(*itr)->Update(_dt);
					}
				}

				// Golden Brick
				if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					(*itr)->Update(_dt);
				}

				// SuperMushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= beginSuperMushroomId) {
					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);
				}

				// GiftBrick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					(*itr)->Update(_dt);
				}

				// ==========================================================================================
				if (this->mario->getState() == DIE
					|| this->mario->getState() == DIE_JUMPING
					|| this->mario->getState() == DIE_DROPPING
					|| this->mario->getState() == SCALING_UP
					|| this->mario->getState() == SCALING_DOWN) {
					continue;
				}

				// Goombas
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					(*itr)->Update(_dt);
				}

				// Koopas
				else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
					(*itr)->Update(_dt);
				}
			}
		}
	}

	if (mario != NULL) {
		mario->Update(_dt);
		Camera::getInstance()->follow(mario, _dt);
	}
	if (this->mario->getState() == DIE
	|| this->mario->getState() == DIE_JUMPING
	|| this->mario->getState() == DIE_DROPPING
	|| this->mario->getState() == SCALING_UP
	|| this->mario->getState() == SCALING_DOWN) {
		return;
	}
	ScoreBoard::getInstance()->Update(_dt);
}

void SunnyVC::viewDidUpdate(float _dt)
{
	if (this->mario->getState() == DIE
		|| this->mario->getState() == DIE_JUMPING
		|| this->mario->getState() == DIE_DROPPING
		|| this->mario->getState() == SCALING_UP
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getIsFlashMode())
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

				// Block
				if (beginBlockId <= (*itr)->getId() && (*itr)->getId() <= endBlockId) {
					this->mario->handleBlockCollision(static_cast<Block*>(*itr), _dt);
				}

				// Golden Brick
				else if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					this->mario->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*itr), _dt);
				}

				// Super Mushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
					if (static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_DISAPPEARED) {
						Grid::getInstance()->remove(*itr, i, j);
						break;
					}

					// Mario vs SuperMushroom
					this->mario->handleSuperMushroomCollision(static_cast<SuperMushroom*>(*itr), _dt);
					static_cast<SuperMushroom*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Super Mushroom collide to others
					for (int r = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); r < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++r) {
						for (int c = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); c < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++c) {
							unordered_set<Component*> superMushroomCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator superMushroomItr;
							for (superMushroomItr = superMushroomCell.begin(); superMushroomItr != superMushroomCell.end(); ++superMushroomItr) {
								// Ground, GoldenBrick, GiftBrick, GreenPipe
								if ((beginGroundId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGroundId)
								|| (beginGoldenBrickId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGoldenBrickId)
								|| (beginGiftBrickId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGiftBrickId)
								|| (beginGreenPipeId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGreenPipeId)) {
									static_cast<SuperMushroom*>(*itr)->handleHardComponentCollision(*superMushroomItr, _dt);
								}
								else if (beginBlockId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endBlockId) {
									static_cast<SuperMushroom*>(*itr)->handleBlockCollision(static_cast<Block*>(*superMushroomItr), _dt);
								}
							}
						}
					}
					
				}

				// Gift Brick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					this->mario->handleGiftBrickCollision(static_cast<GiftBrick*>(*itr), _dt);
				}

				// Green Pipe
				else if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
					this->mario->handleGreenPipeCollision(static_cast<GreenPipe*>(*itr), _dt);
				}

				// Goombas
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					if (static_cast<Goomba*>(*itr)->getState() == DEAD_GOOMBA) {
						Grid::getInstance()->remove(*itr, i, j);
						this->goombas->erase(static_cast<Goomba*>(*itr));
						break;
					}

					// Mario vs Goomba
					this->mario->handleGoombaCollision(static_cast<Goomba*>(*itr), _dt);
					static_cast<Goomba*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Goomba to others
					int beginRowGoomba = floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int endRowGoomba = ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int beginColGoomba = floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());
					int endColGoomba = ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());

					beginRowGoomba = beginRowGoomba < 0 ? 0 : beginRowGoomba;
					endRowGoomba = endRowGoomba > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowGoomba;
					beginColGoomba = beginColGoomba < 0 ? 0 : beginColGoomba;
					endColGoomba = endColGoomba > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColGoomba;

					for (int r = beginRowGoomba; r < endRowGoomba; ++r) {
						for (int c = beginColGoomba; c < endColGoomba; ++c) {
							unordered_set<Component*> goombaCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator goombaItr;
							for (goombaItr = goombaCell.begin(); goombaItr != goombaCell.end(); ++goombaItr) {
								if ((beginGroundId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGroundId)
								|| (beginGoldenBrickId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGoldenBrickId)
								|| (beginGiftBrickId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGiftBrickId)
								|| (beginGreenPipeId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGreenPipeId)) {
									static_cast<Goomba*>(*itr)->handleHardComponentCollision(*goombaItr, _dt);
								}
								else if (beginBlockId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endBlockId) {
									static_cast<Goomba*>(*itr)->handleBlockCollision(*goombaItr, _dt);
								}
							}
						}
					}

					if (static_cast<Goomba*>(*itr)->getIsStandOnSurface() == false && static_cast<Goomba*>(*itr)->getState() == GOOMBA_MOVING_LEFT) {
						static_cast<Goomba*>(*itr)->setState(GoombaState::GOOMBA_DROPPING_LEFT);
						return;
					}
					else if (static_cast<Goomba*>(*itr)->getIsStandOnSurface() == false && static_cast<Goomba*>(*itr)->getState() == GOOMBA_MOVING_RIGHT) {
						static_cast<Goomba*>(*itr)->setState(GoombaState::GOOMBA_DROPPING_RIGHT);
						return;
					}
				}

				// Koopas
				else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
					if (static_cast<Koopa*>(*itr)->getState() == KOOPA_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->koopas->erase(static_cast<Koopa*>(*itr));
					}

					// Mario vs Koopa
					//static_cast<Koopa*>(*itr)->setHasCollideMario(false);
					this->mario->handleKoopaCollision(static_cast<Koopa*>(*itr), _dt);
					static_cast<Koopa*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Koopa to others
					int beginRowKoopa = floor(((*itr)->getY() - (Camera::getInstance()->getHeight())) / Grid::getInstance()->getCellHeight());
					int endRowKoopa = ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight())) / Grid::getInstance()->getCellHeight());
					int beginColKoopa = floor(((*itr)->getX() - (Camera::getInstance()->getWidth())) / Grid::getInstance()->getCellWidth());
					int endColKoopa = ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth())) / Grid::getInstance()->getCellWidth());

					beginRowKoopa = beginRowKoopa < 0 ? 0 : beginRowKoopa;
					endRowKoopa = endRowKoopa > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowKoopa;
					beginColKoopa = beginColKoopa < 0 ? 0 : beginColKoopa;
					endColKoopa = endColKoopa > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColKoopa;

					for (int r = beginRowKoopa; r < endRowKoopa; ++r) {
						for (int c = beginColKoopa; c < endColKoopa; ++c) {
							unordered_set<Component*> koopaCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator koopaItr;
							for (koopaItr = koopaCell.begin(); koopaItr != koopaCell.end(); ++koopaItr) {
								if ((beginGroundId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGroundId)
									|| (beginGoldenBrickId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGoldenBrickId)
									|| (beginGiftBrickId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGiftBrickId)
									|| (beginGreenPipeId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGreenPipeId)) {
									static_cast<Koopa*>(*itr)->handleHardComponentCollision(*koopaItr, _dt);
								}
								else if (beginBlockId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endBlockId) {
									static_cast<Koopa*>(*itr)->handleBlockCollision(*koopaItr, _dt);
								}
							}
						}
					}

					if (static_cast<Koopa*>(*itr)->getIsStandOnSurface() == false && static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
						static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
					}
					else if (static_cast<Koopa*>(*itr)->getIsStandOnSurface() == false && static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
						static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
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
					// Golden Brick
					if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
						(*itr)->Draw(map->getTexture());
					}

					// Super Mushroom
					else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= beginSuperMushroomId) {
						(*itr)->Draw(map->getTexture());
					}

					// Gift Brick
					else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
						(*itr)->Draw(map->getTexture());
					}

					// Green Pipe
					else if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
						(*itr)->Draw(map->getTexture());
					}

					// Goomba
					else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
						(*itr)->Draw(map->getTexture());
					}

					// Koopas
					else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
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

void SunnyVC::adaptRangeID(vector<string> data, char seperator)
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
			this->beginBlockId = v[0];
			this->endBlockId = v[1];
		}
		else if (i == 2) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGoldenBrickId = v[0];
			this->endGoldenBrickId = v[1];
		}
		else if (i == 3) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginSuperMushroomId = v[0];
			this->endSuperMushroomId = v[1];
		}
		else if (i == 4) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGiftBrickId = v[0];
			this->endGiftBrickId = v[1];
		}
		else if (i == 5) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGreenPipeId = v[0];
			this->endGreenPipeId = v[1];
		}
		else if (i == 6) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGoombaId = v[0];
			this->endGoombaId = v[1];
		}
		else if (i == 7) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginKoopaId = v[0];
			this->endKoopaId = v[1];
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

		if (line == "<SunnyVC>") {
			section = SECTION_SUNNY_VC;
			continue;
		}
		else if (line == "</SunnyVC>") {
			this->adaptRangeID(data, ',');
			section = SECTION_NONE;
		}
		else if (line == "<Camera>") {
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
		else if (line == "<KoopaFrames>") {
			section = SECTION_KOOPA_FRAMES;
			continue;
		}
		else if (line == "</KoopaFrames>") {
			for (int i = 0; i < data.size(); ++i) {
				Koopa* koopa = new Koopa(0, 0, 0, 0, 0, 0, 0);
				koopa->loadInfo(data[i], ',');
				koopas->insert(koopa);
			}
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
		case SECTION_SUNNY_VC:
			data.push_back(line);
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
		case SECTION_GROUNDS:
			data.push_back(line);
			break;
		case SECTION_BLOCK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GIFT_BRICK_FRAMES:
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
		case SECTION_KOOPA_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GRID_INFO:
			Grid::getInstance()->loadInfo(line, ',');
			break;
		case SECTION_GRID_MATRIX_ID:
			data.push_back(line);
			break;
		case SECTION_ANIMATION_BUNDLE:
			data.push_back(line);
			break;
		default:
			break;
		}
	}

	fs.close();
}

void SunnyVC::adaptAnimation()
{
	// Golden Bricks
	for (int i = 0; i < this->goldenBricks->size(); ++i) {
		this->goldenBricks->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getGoldenBrick()));
	}

	// Gift Bricks
	for (int i = 0; i < this->giftBricks->size(); ++i) {
		this->giftBricks->at(i)->setState(GiftBrickState::FULLGIFTBRICK);
		if (this->giftBricks->at(i)->getGiftType() == SuperMushroomGift) { // Super Mushroom
			this->giftBricks->at(i)->setSuperMushroomState(SuperMushroomState::SUPER_MUSHROOM_GROWING_UP);
		}
	}

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		this->greenPipes->at(i)->setupAnimation();
	}

	///
	/// --------------------------- Enemies ---------------------------
	///

	// Goombas
	unordered_set<Goomba*> ::iterator goombaItr;
	for (goombaItr = this->goombas->begin(); goombaItr != this->goombas->end(); ++goombaItr) {
		if ((*goombaItr)->getVx() > 0) {
			(*goombaItr)->setState(GoombaState::GOOMBA_MOVING_RIGHT);
		}
		else if ((*goombaItr)->getVx() < 0) {
			(*goombaItr)->setState(GoombaState::GOOMBA_MOVING_LEFT);
		}
		else {
			(*goombaItr)->setState(GoombaState::GOOMBA_STANDING);
		}
	}

	// Koopas
	unordered_set<Koopa*> ::iterator koopaItr;
	for (koopaItr = this->koopas->begin(); koopaItr != this->koopas->end(); ++koopaItr) {
		if ((*koopaItr)->getVx() >= 0) {
			(*koopaItr)->setState(KoopaState::KOOPA_MOVING_RIGHT);
		}
		else if ((*koopaItr)->getVx() < 0) {
			(*koopaItr)->setState(KoopaState::KOOPA_MOVING_LEFT);
		}
	}

	this->mario->setState(MarioState::DROPPING);
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
		Grid::getInstance()->add(this->giftBricks->at(i));
	}

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		Grid::getInstance()->add(this->greenPipes->at(i));
	}

	///
	/// --------------------------- Enemies ---------------------------
	///

	// Goombas
	unordered_set<Goomba*> ::iterator goombaItr;
	for (goombaItr = this->goombas->begin(); goombaItr != this->goombas->end(); ++goombaItr) {
		Grid::getInstance()->add(*goombaItr);
	}

	// Koopas
	unordered_set<Koopa*> ::iterator koopaItr;
	for (koopaItr = this->koopas->begin(); koopaItr != this->koopas->end(); ++koopaItr) {
		Grid::getInstance()->add(*koopaItr);
	}
}