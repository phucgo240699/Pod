#include "ThirdVC.h"

Mario* ThirdVC::getMario()
{
    return this->mario;
}

int ThirdVC::getLeftAnchorDroppingFromCloudy()
{
	return this->leftAnchorDroppingFromCloudy;
}

int ThirdVC::getTopAnchorDroppingFromCloudy()
{
	return this->topAnchorDroppingFromCloudy;
}

void ThirdVC::setMario(Mario* _mario)
{
    this->mario = _mario;
}

void ThirdVC::viewDidLoad()
{
    mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
    map = new Map();
	grounds = new vector<Ground*>();
	blocks = new vector<Block*>();
	goldenBricks = new unordered_set<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();
	coins = new unordered_set<Coin*>();
	goombas = new unordered_set<Goomba*>();
	koopas = new unordered_set<Koopa*>();
	musicBoxes = new vector<MusicBox*>();
	boomerangBros = new unordered_set<BoomerangBro*>();
	bosses = new unordered_set<Boss*>();
	bombs = new vector<Bomb*>();
	items = new unordered_set<Item*>();

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
	for (size_t i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::number_5) {
			if (this->mario->getX() != float(1250) || this->mario->getY() != float(300)) {
				this->mario->setX(float(1250));
				this->mario->setY(float(300));
				Camera::getInstance()->setPositionBy(this->mario);
			}
		}
	}
    mario->onKeyDown(_keyTypes);
}

void ThirdVC::viewWillUpdate(float _dt)
{
	// Check by cell in grid
	int beginRow = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRow = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginCol = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endCol = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));
	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			if (cell.size() <= 0) continue;

			unordered_set<Component*> ::iterator itr;
			for (itr = cell.begin(); itr != cell.end(); ++itr) {

				// Golden Brick
				if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// GiftBrick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// SuperMushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// SuperLeaf
				else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				//// ==========================================================================================
				//if (this->mario->getState() == DIE
				//	|| this->mario->getState() == DIE_JUMPING
				//	|| this->mario->getState() == DIE_DROPPING
				//	|| this->mario->getState() == SCALING_UP
				//	|| this->mario->getState() == SCALING_DOWN
				//	|| this->mario->getState() == TRANSFERING_TO_FLY
				//	|| this->mario->getState() == DROPPING_DOWN_PIPE
				//	|| this->mario->getState() == POPPING_UP_PIPE
				//	|| this->mario->getState() == JUMPING_UP_TO_CLOUND
				//	|| this->mario->getState() == DROPPING_DOWN_WIN
				//	|| this->mario->getState() == MOVING_RIGHT_WIN) {
				//	continue;
				//}


				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Goombas
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Koopas
				else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Music Box
				else if (beginMusicBoxId <= (*itr)->getId() && (*itr)->getId() <= endMusicBoxId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Boomerang Bro
				else if (beginBoomerangBroId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangBroId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Boomerang
				else if (beginBoomerangId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Boss
				else if (beginBossId <= (*itr)->getId() && (*itr)->getId() <= endBossId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Bomb
				else if (beginBombId <= (*itr)->getId() && (*itr)->getId() <= endBombId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Item
				else if (beginItemId <= (*itr)->getId() && (*itr)->getId() <= endItemId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}
			}
		}
	}
}

void ThirdVC::viewUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}
	
	
	// Check by cell in grid
	int beginRow = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRow = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginCol = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endCol = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));
	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

		if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

		unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
			if (cell.size() <= 0) continue;

			unordered_set<Component*> ::iterator itr;
			for (itr = cell.begin(); itr != cell.end(); ++itr) {

				// Golden Brick
				if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<GoldenBrick*>(*itr)->getState() == GOLDEN_BRICK_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->goldenBricks->erase(static_cast<GoldenBrick*>(*itr));
						continue;
					}
					(*itr)->Update(_dt);
				}

				// GiftBrick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					(*itr)->Update(_dt);
				}

				// SuperMushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_DISAPPEARED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					if (this->mario->getState() == DIE
						|| this->mario->getState() == DIE_JUMPING
						|| this->mario->getState() == DIE_DROPPING
						|| this->mario->getState() == SCALING_DOWN
						|| this->mario->getState() == TRANSFERING_TO_FLY
						|| this->mario->getState() == DROPPING_DOWN_PIPE
						|| this->mario->getState() == POPPING_UP_PIPE
						|| this->mario->getState() == JUMPING_UP_TO_CLOUND
						|| this->mario->getState() == DROPPING_DOWN_WIN
						|| this->mario->getState() == MOVING_RIGHT_WIN) {
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// SuperLeaf
				else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<SuperLeaf*>(*itr)->getState() == SUPER_LEAF_DISAPPEARED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					if (this->mario->getState() == DIE
						|| this->mario->getState() == DIE_JUMPING
						|| this->mario->getState() == DIE_DROPPING
						|| this->mario->getState() == SCALING_DOWN
						|| this->mario->getState() == TRANSFERING_TO_FLY
						|| this->mario->getState() == DROPPING_DOWN_PIPE
						|| this->mario->getState() == POPPING_UP_PIPE
						|| this->mario->getState() == JUMPING_UP_TO_CLOUND
						|| this->mario->getState() == DROPPING_DOWN_WIN
						|| this->mario->getState() == MOVING_RIGHT_WIN) {
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);
				}

				// ==========================================================================================
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
					|| this->mario->getState() == MOVING_RIGHT_WIN) {
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

					//Grid::getInstance()->updateCellOf(*itr);
				}

				// Goombas
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Goomba*>(*itr)->getState() == DEAD_GOOMBA) {
						Grid::getInstance()->remove(*itr, i, j);
						this->goombas->erase(static_cast<Goomba*>(*itr));
						continue;
					}

					static_cast<Goomba*>(*itr)->setMarioX(this->mario->getX());
					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Koopas
				else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Koopa*>(*itr)->getState() == KOOPA_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->koopas->erase(static_cast<Koopa*>(*itr));
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Music Box
				else if (beginMusicBoxId <= (*itr)->getId() && (*itr)->getId() <= endMusicBoxId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					(*itr)->Update(_dt);
				}

				// Boomerang Bro
				else if (beginBoomerangBroId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangBroId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<BoomerangBro*>(*itr)->getState() != BOOMERANG_BRO_BEING_DEAD) {
						static_cast<BoomerangBro*>(*itr)->setIsFlip(this->mario->getX() + this->mario->getBoundsWidth() < (*itr)->getX());
						static_cast<BoomerangBro*>(*itr)->setMarioX(this->mario->getX());
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Boomerang
				else if (beginBoomerangId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Boomerang*>(*itr)->getState() == BOOMERANG_STAYING) {
						Grid::getInstance()->remove(*itr, i, j);
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->isCollidingByFrame(Camera::getInstance()->getFrame()) == false) {
						static_cast<Boomerang*>(*itr)->setState(BoomerangState::BOOMERANG_STAYING);
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Boss
				else if (beginBossId <= (*itr)->getId() && (*itr)->getId() <= endBossId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Boss*>(*itr)->getState() == BOSS_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->bosses->erase(static_cast<Boss*>(*itr));
						continue;
					}

					static_cast<Boss*>(*itr)->setMarioX(this->mario->getX());
					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Bomb
				else if (beginBombId <= (*itr)->getId() && (*itr)->getId() <= endBombId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Bomb*>(*itr)->getState() == BOMB_STAYING) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						static_cast<Bomb*>(*itr)->setState(BombState::BOMB_STAYING);
						Grid::getInstance()->remove(*itr, i, j);
					}
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

				// Item
				else if (beginItemId <= (*itr)->getId() && (*itr)->getId() <= endItemId) {
				// Prevent update mullti time in one loop
				if ((*itr)->getIsUpdatedInOneLoop()) continue;

				if (static_cast<Item*>(*itr)->getState() == ITEM_DISAPPEARD) {
					Grid::getInstance()->remove(*itr, i, j);
				}

				(*itr)->Update(_dt);
				}
			}
		}
	}


	if (mario != NULL) {
		mario->Update(_dt);

		if (this->mario->getState() == MarioState::JUMPING_UP_TO_CLOUND) {
			if (this->mario->getY() + this->mario->getHeight() < Camera::getInstance()->getY()) {
				this->navigateTo(SceneName::CloudyScene);
				return;
			}
		}
		else if (this->mario->getState() == DROPPING_DOWN_WIN) {
			return;
		}
		else if (this->mario->getState() == MOVING_RIGHT_WIN) {
			if (mario->getX() >= Camera::getInstance()->getLimitX()) {
				this->navigateTo(SceneName::WorldScene);
			}
			return;
		}

		// Navigate to WorldVC when Mario drop out of map to far
		if (this->mario->getY() >= Camera::getInstance()->getLimitY() + 100) {
			this->mario->setIsFireMode(false);
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

	if (ScoreBoard::getInstance()->getTime() <= 0) {
		this->mario->setIsFireMode(false);
		this->mario->setIsSuperMode(false);
		this->mario->setIsFlyingMode(false);
		this->mario->setIsPreFlyingUpMode(false);
		this->mario->setIsFlyingUpMode(false);

		this->mario->setState(MarioState::DIE);
	}
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
		|| this->mario->getState() == MOVING_RIGHT_WIN)
	{
		return;
	}

	if (this->mario->getIsStandOnSurface() == true) {
		this->mario->setIsStandOnSurface(false);
	}

	// Check by cell in grid
	unordered_set<Component*> marioCell;
	int beginRowMario = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRowMario = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginColMario = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endColMario = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));
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

				// Block
				else if (beginBlockId <= (*itr)->getId() && (*itr)->getId() <= endBlockId) {
					this->mario->handleBlockCollision(static_cast<Block*>(*itr), _dt);
				}

				// Golden Brick
				else if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					this->mario->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*itr), _dt);
				}

				// Gift Brick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					this->mario->handleGiftBrickCollision(static_cast<GiftBrick*>(*itr), _dt);
				}


				// Super Mushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
					// Mario vs SuperMushroom
					if (this->mario->getIsFlashMode() == false) {
						this->mario->handleSuperMushroomCollision(static_cast<SuperMushroom*>(*itr), _dt);
						static_cast<SuperMushroom*>(*itr)->handleMarioCollision(this->mario, _dt);
					}

					// Super Mushroom collide to others
					int beginRowSuperMushroom = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowSuperMushroom = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColSuperMushroom = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColSuperMushroom = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

					beginRowSuperMushroom = beginRowSuperMushroom < 0 ? 0 : beginRowSuperMushroom;
					endRowSuperMushroom = endRowSuperMushroom > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowSuperMushroom;
					beginColSuperMushroom = beginColSuperMushroom < 0 ? 0 : beginColSuperMushroom;
					endColSuperMushroom = endColSuperMushroom > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColSuperMushroom;

					for (int r = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight())); r < int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight())); ++r) {
						for (int c = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth())); c < int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth())); ++c) {
							unordered_set<Component*> superMushroomCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator superMushroomItr;
							for (superMushroomItr = superMushroomCell.begin(); superMushroomItr != superMushroomCell.end(); ++superMushroomItr) {
								// Ground, GoldenBrick, GiftBrick, GreenPipe
								if ((beginGroundId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGroundId)
									|| (beginGoldenBrickId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGoldenBrickId)
									|| (beginGiftBrickId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGiftBrickId)
									/*|| (beginGreenPipeId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGreenPipeId)*/) {
									static_cast<SuperMushroom*>(*itr)->handleHardComponentCollision(*superMushroomItr, _dt);
								}
								else if (beginBlockId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endBlockId) {
									static_cast<SuperMushroom*>(*itr)->handleBlockCollision(static_cast<Block*>(*superMushroomItr), _dt);
								}
							}
						}
					}

					if (static_cast<SuperMushroom*>(*itr)->getIsStandOnSurface() == false && static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_MOVING_LEFT) {
						static_cast<SuperMushroom*>(*itr)->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_LEFT);
						return;
					}
					else if (static_cast<SuperMushroom*>(*itr)->getIsStandOnSurface() == false && static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_MOVING_RIGHT) {
						static_cast<SuperMushroom*>(*itr)->setState(SuperMushroomState::SUPER_MUSHROOM_DROPPING_RIGHT);
						return;
					}
				}

				// Super Leaf
				else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
					if (this->mario->getIsFlashMode() == false) {
						// Mario vs SuperLeaf
						this->mario->handleSuperLeafCollision(static_cast<SuperLeaf*>(*itr), _dt);
						static_cast<SuperLeaf*>(*itr)->handleMarioCollision(this->mario, _dt);
					}
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					this->mario->handleCoinCollision(static_cast<Coin*>(*itr), _dt);
					static_cast<Coin*>(*itr)->handleMarioCollision(this->mario, _dt);
				}

				// Goombas
				else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {

					// Mario vs Goomba
					if (this->mario->getIsFlashMode() == false) {
						this->mario->handleGoombaCollision(static_cast<Goomba*>(*itr), _dt);
						static_cast<Goomba*>(*itr)->handleMarioCollision(this->mario, _dt);
					}

					// Goomba to others
					int beginRowGoomba = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowGoomba = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColGoomba = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColGoomba = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

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
									/*|| (beginGreenPipeId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGreenPipeId)*/) {
									static_cast<Goomba*>(*itr)->handleHardComponentCollision(*goombaItr, _dt);
								}
								else if (beginBlockId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endBlockId) {
									static_cast<Goomba*>(*itr)->handleBlockCollision(*goombaItr, _dt);
								}
								else if (beginKoopaId <= (*goombaItr)->getId() && (*goombaItr)->getId() < endKoopaId) {
									static_cast<Goomba*>(*itr)->handleKoopaCollision(static_cast<Koopa*>(*goombaItr), _dt);
								}
								else if (beginFireBallId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endFireBallId) {
									static_cast<Goomba*>(*itr)->handleFireBallCollision(static_cast<FireBall*>(*goombaItr), _dt);
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

					// Mario vs Koopa
					//if (this->mario->getIsFlashMode() == false) {
					this->mario->handleKoopaCollision(static_cast<Koopa*>(*itr), _dt);
					static_cast<Koopa*>(*itr)->handleMarioCollision(this->mario, _dt);
					//}

					// Koopa to others
					int beginRowKoopa = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowKoopa = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColKoopa = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColKoopa = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

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
									/*|| (beginGreenPipeId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGreenPipeId)*/) {
									static_cast<Koopa*>(*itr)->handleHardComponentCollision(*koopaItr, _dt);
								}
								else if (beginGiftBrickId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGiftBrickId) {
									static_cast<Koopa*>(*itr)->handleGiftBrickCollision(static_cast<GiftBrick*>(*koopaItr), this->mario, _dt);
								}
								else if (beginBlockId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endBlockId) {
									static_cast<Koopa*>(*itr)->handleBlockCollision(*koopaItr, _dt);
								}
								else if (beginGoombaId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGoombaId) {
									static_cast<Koopa*>(*itr)->handleGoombaCollision(static_cast<Goomba*>(*koopaItr), _dt);
								}
								else if (beginFireBallId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endFireBallId) {
									static_cast<Koopa*>(*itr)->handleFireBallCollision(static_cast<FireBall*>(*koopaItr), _dt);
								}
								else if (beginGoldenBrickId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGoldenBrickId) {
									static_cast<Koopa*>(*itr)->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*koopaItr), _dt);
								}
								else if (beginKoopaId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endKoopaId) {
									if ((*itr)->getId() != (*koopaItr)->getId()) {
										static_cast<Koopa*>(*itr)->handleKoopaCollision(static_cast<Koopa*>(*koopaItr), _dt);
									}
								}
								else if (beginMusicBoxId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endMusicBoxId) {
									static_cast<Koopa*>(*itr)->handleMusicBoxCollision(static_cast<MusicBox*>(*koopaItr), _dt);
								}
								else if (beginBoomerangBroId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endBoomerangBroId) {
									static_cast<Koopa*>(*itr)->handleBoomerangBroCollision(static_cast<BoomerangBro*>(*koopaItr), _dt);
								}
								else if (beginBossId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endBossId) {
									static_cast<Koopa*>(*itr)->handleBossCollision(static_cast<Boss*>(*koopaItr), _dt);
								}
							}
						}
					}

					if (static_cast<Koopa*>(*itr)->getIsStandOnSurface() == false && static_cast<Koopa*>(*itr)->getState() != KOOPA_FLYING_LEFT && static_cast<Koopa*>(*itr)->getState() != KOOPA_FLYING_RIGHT) {
						if (static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
						}
						else if (static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
						}
						else if (/*static_cast<Koopa*>(*itr)->getIsGreenMode() && */static_cast<Koopa*>(*itr)->getState() == KOOPA_MOVING_LEFT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_DROPPING_LEFT);
						}
						else if (/*static_cast<Koopa*>(*itr)->getIsGreenMode() && */static_cast<Koopa*>(*itr)->getState() == KOOPA_MOVING_RIGHT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_DROPPING_RIGHT);
						}
					}

				}

				// Music Box
				else if (beginMusicBoxId <= (*itr)->getId() && (*itr)->getId() <= endMusicBoxId) {
					this->mario->handleMusicBoxCollision(static_cast<MusicBox*>(*itr), _dt);
				}


				// Boomerang Bro
				else if (beginBoomerangBroId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangBroId) {
					this->mario->handleBoomerangBroCollision(static_cast<BoomerangBro*>(*itr), _dt);
					static_cast<BoomerangBro*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Boomerang Bro to others
					int beginRowBoomerangBro = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowBoomerangBro = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColBoomerangBro = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColBoomerangBro = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

					beginRowBoomerangBro = beginRowBoomerangBro < 0 ? 0 : beginRowBoomerangBro;
					endRowBoomerangBro = endRowBoomerangBro > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowBoomerangBro;
					beginColBoomerangBro = beginColBoomerangBro < 0 ? 0 : beginColBoomerangBro;
					endColBoomerangBro = endColBoomerangBro > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColBoomerangBro;

					for (int r = beginRowBoomerangBro; r < endRowBoomerangBro; ++r) {
						for (int c = beginColBoomerangBro; c < endColBoomerangBro; ++c) {
							unordered_set<Component*> boomerangBroCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator boomerangBroItr;

							for (boomerangBroItr = boomerangBroCell.begin(); boomerangBroItr != boomerangBroCell.end(); ++boomerangBroItr) {
								if (beginGroundId <= (*boomerangBroItr)->getId() && (*boomerangBroItr)->getId() <= endGroundId) {
									static_cast<BoomerangBro*>(*itr)->hanldeHardComponentCollision(*boomerangBroItr, _dt);
								}
								else if (beginFireBallId <= (*boomerangBroItr)->getId() && (*boomerangBroItr)->getId() <= endFireBallId) {
									static_cast<BoomerangBro*>(*itr)->handleFireBallCollision(static_cast<FireBall*>(*boomerangBroItr), _dt);
								}
								else if (beginKoopaId <= (*boomerangBroItr)->getId() && (*boomerangBroItr)->getId() <= endKoopaId) {
									static_cast<BoomerangBro*>(*itr)->handleKoopaCollision(static_cast<Koopa*>(*boomerangBroItr), _dt);
								}
							}
						}
					}					
				}

				// Boomerang
				else if (beginBoomerangId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangId) {
					this->mario->handleBoomerangCollision(static_cast<Boomerang*>(*itr), _dt);
					static_cast<Boomerang*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Boomerang to others
					int beginRowBoomerang = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowBoomerang = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColBoomerang = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColBoomerang = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

					beginRowBoomerang = beginRowBoomerang < 0 ? 0 : beginRowBoomerang;
					endRowBoomerang = endRowBoomerang > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowBoomerang;
					beginColBoomerang = beginColBoomerang < 0 ? 0 : beginColBoomerang;
					endColBoomerang = endColBoomerang > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColBoomerang;

					for (int r = beginRowBoomerang; r < endRowBoomerang; ++r) {
						for (int c = beginColBoomerang; c < endColBoomerang; ++c) {
							unordered_set<Component*> boomerangCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator boomerangItr;

							for (boomerangItr = boomerangCell.begin(); boomerangItr != boomerangCell.end(); ++boomerangItr) {
								if (beginBoomerangBroId <= (*boomerangItr)->getId() && (*boomerangItr)->getId() <= endBoomerangBroId) {
									static_cast<Boomerang*>(*itr)->hanldeBoomerangBroCollision(static_cast<BoomerangBro*>(*boomerangItr), _dt);
								}
							}
						}
					}
				}

				// Boss
				else if (beginBossId <= (*itr)->getId() && (*itr)->getId() <= endBossId) {
					this->mario->handleBossCollision(static_cast<Boss*>(*itr), _dt);
					static_cast<Boss*>(*itr)->handleMarioCollision(this->mario, _dt);

					// Boss to others
					int beginRowBoss = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowBoss = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColBoss = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColBoss = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

					beginRowBoss = beginRowBoss < 0 ? 0 : beginRowBoss;
					endRowBoss = endRowBoss > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowBoss;
					beginColBoss = beginColBoss < 0 ? 0 : beginColBoss;
					endColBoss = endColBoss > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColBoss;

					for (int r = beginRowBoss; r < endRowBoss; ++r) {
						for (int c = beginColBoss; c < endColBoss; ++c) {
							unordered_set<Component*> bossCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator bossItr;

							for (bossItr = bossCell.begin(); bossItr != bossCell.end(); ++bossItr) {
								if (beginGroundId <= (*bossItr)->getId() && (*bossItr)->getId() <= endGroundId
									|| beginGoldenBrickId <= (*bossItr)->getId() && (*bossItr)->getId() <= endGoldenBrickId
									|| beginGiftBrickId <= (*bossItr)->getId() && (*bossItr)->getId() <= endGiftBrickId) {
									static_cast<Boss*>(*itr)->handleHardComponentCollision(*bossItr, _dt);
								}
								else if (beginBlockId <= (*bossItr)->getId() && (*bossItr)->getId() <= endBlockId) {
									static_cast<Boss*>(*itr)->handleBlockComponentCollision(*bossItr, _dt);
								}
								else if (beginFireBallId <= (*bossItr)->getId() && (*bossItr)->getId() <= endFireBallId) {
									static_cast<Boss*>(*itr)->handleFireBallCollision(static_cast<FireBall*>(*bossItr), _dt);
								}
								else if (beginKoopaId <= (*bossItr)->getId() && (*bossItr)->getId() <= endKoopaId) {
									static_cast<Boss*>(*itr)->handleKoopaCollision(static_cast<Koopa*>(*bossItr), _dt);
								}

							}
						}
					}

					if (static_cast<Boss*>(*itr)->getIsStandOnSurface() == false && static_cast<Boss*>(*itr)->getState() == BOSS_MOVING_LEFT) {
						static_cast<Boss*>(*itr)->setState(BOSS_DROPPING_LEFT);
					}
					else if (static_cast<Boss*>(*itr)->getIsStandOnSurface() == false && static_cast<Boss*>(*itr)->getState() == BOSS_MOVING_RIGHT) {
						static_cast<Boss*>(*itr)->setState(BOSS_DROPPING_RIGHT);
					}
				}


				// Bomb
				else if (beginBombId <= (*itr)->getId() && (*itr)->getId() <= endBombId) {
					this->mario->handleBombCollision(static_cast<Bomb*>(*itr), _dt);
					static_cast<Bomb*>(*itr)->handleMarioCollision(this->mario, _dt);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// FireBall to others
					int beginRowFireball = int(floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int endRowFireball = int(ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight()));
					int beginColFireball = int(floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));
					int endColFireball = int(ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth()));

					beginRowFireball = beginRowFireball < 0 ? 0 : beginRowFireball;
					endRowFireball = endRowFireball > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowFireball;
					beginColFireball = beginColFireball < 0 ? 0 : beginColFireball;
					endColFireball = endColFireball > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColFireball;

					for (int r = beginRowFireball; r < endRowFireball; ++r) {
						for (int c = beginColFireball; c < endColFireball; ++c) {
							unordered_set<Component*> fireBallCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator fireBallItr;

							for (fireBallItr = fireBallCell.begin(); fireBallItr != fireBallCell.end(); ++fireBallItr) {
								if (beginGroundId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGroundId) {
									static_cast<FireBall*>(*itr)->handleHardComponentCollision(*fireBallItr, _dt);
								}
								else if (beginBlockId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endBlockId) {
									static_cast<FireBall*>(*itr)->handleBlockCollision(static_cast<Block*>(*fireBallItr), _dt);
								}
								else if (beginGoombaId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGoombaId) {
									static_cast<FireBall*>(*itr)->handleGoombaCollision(static_cast<Goomba*>(*fireBallItr), _dt);
								}
								else if (beginKoopaId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endKoopaId) {
									static_cast<FireBall*>(*itr)->handleKoopaCollision(static_cast<Koopa*>(*fireBallItr), _dt);
								}
								else if (beginGoldenBrickId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGoldenBrickId) {
									static_cast<FireBall*>(*itr)->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*fireBallItr), _dt);
								}
								else if (beginBoomerangBroId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endBoomerangBroId) {
									static_cast<FireBall*>(*itr)->handleBoomerangBroCollision(static_cast<BoomerangBro*>(*fireBallItr), _dt);
								}
								else if (beginBossId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endBossId) {
									static_cast<FireBall*>(*itr)->handleBossCillision(static_cast<Boss*>(*fireBallItr), _dt);
								}
							}
						}
					}
				}


				// Item
				else if (beginItemId <= (*itr)->getId() && (*itr)->getId() <= endItemId) {
					this->mario->handleItemCollision(static_cast<Item*>(*itr), _dt);
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
			map->Draw(Drawing::getInstance()->getThirdMapTexture());
		}

		for (int i = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight())); i < int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight())); ++i) {
			for (int j = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth())); j < int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth())); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {
					// Golden Brick
					if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Gift Brick
					else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Super Mushroom
					else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// SuperLeaf
					else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Coin
					else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Goomba
					else if (beginGoombaId <= (*itr)->getId() && (*itr)->getId() <= endGoombaId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Koopas
					else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Music Box
					else if (beginMusicBoxId <= (*itr)->getId() && (*itr)->getId() <= endMusicBoxId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Boomerang Bro
					else if (beginBoomerangBroId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangBroId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Item
					else if (beginItemId <= (*itr)->getId() && (*itr)->getId() <= endItemId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}
				}
			}
		}

		if (mario != NULL) {
			mario->Draw();
		}
		
		for (int i = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight())); i < int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight())); ++i) {
			for (int j = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth())); j < int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth())); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {

					// Boomerang
					if (beginBoomerangId <= (*itr)->getId() && (*itr)->getId() <= endBoomerangId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Fire Ball
					else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Bomb
					else if (beginBombId <= (*itr)->getId() && (*itr)->getId() <= endBombId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}
				}
			}
		}

		for (int i = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight())); i < int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight())); ++i) {
			for (int j = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth())); j < int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth())); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {

					// Boss
					if (beginBossId <= (*itr)->getId() && (*itr)->getId() <= endBossId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
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

void ThirdVC::viewDidRender()
{
}

void ThirdVC::viewWillRelease()
{
}

void ThirdVC::adaptRangeID(vector<string> data, char seperator)
{
	vector<int> v;
	for (size_t i = 0; i < data.size(); ++i) {
		if (i == 0) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGroundId = v[0];
			this->endGroundId = v[1];
			this->leftAnchorDroppingFromCloudy = v[2];
			this->topAnchorDroppingFromCloudy = v[3];
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
			this->beginGiftBrickId = v[0];
			this->endGiftBrickId = v[1];
			this->beginSuperMushroomId = v[2];
			this->endSuperMushroomId = v[3];
			this->beginSuperLeafId = v[4];
			this->endSuperLeafId = v[5];
		}
		else if (i == 4) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginCoinId = v[0];
			this->endCoinId = v[1];
		}
		else if (i == 5) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGoombaId = v[0];
			this->endGoombaId = v[1];
		}
		else if (i == 6) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginKoopaId = v[0];
			this->endKoopaId = v[1];
		}
		else if (i == 7) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginMusicBoxId = v[0];
			this->endMusicBoxId = v[1];
		}
		else if (i == 8) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginBoomerangBroId = v[0];
			this->endBoomerangBroId = v[1];
			this->beginBoomerangId = v[2];
			this->endBoomerangId = v[3];
		}
		else if (i == 9) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginBossId = v[0];
			this->endBossId = v[1];
			this->beginBombId = v[2];
			this->endBombId = v[3];
		}
		else if (i == 10) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginFireBallId = v[0];
			this->endFireBallId = v[1];
		}
		else if (i == 11) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginItemId = v[0];
			this->endItemId = v[1];
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
			for (size_t i = 0; i < data.size(); ++i) {
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
			for (size_t i = 0; i < data.size(); ++i) {
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
			for (size_t i = 0; i < data.size(); ++i) {
				GoldenBrick* goldenBrick = new GoldenBrick(0, 0, 0, 0, 0, 0, 0);
				goldenBrick->loadInfo(data[i], ',');
				this->goldenBricks->insert(goldenBrick);
			}
			section = SECTION_NONE;
		}
		else if (line == "<GiftBrickFrames>") {
			section = SECTION_GIFT_BRICK_FRAMES;
			continue;
		}
		else if (line == "</GiftBrickFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				GiftBrick* giftBrick = new GiftBrick(0, 0, 0, 0, 0, 0);
				giftBrick->loadInfo(data[i], ',');
				giftBricks->push_back(giftBrick);
			}
			section = SECTION_NONE;
		}
		else if (line == "<CoinFrames>") {
			section = SECTION_COIN_FRAMES;
			continue;
		}
		else if (line == "</CoinFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				Coin* coin = new Coin(0, 0, 0, 0, 0, 0, 0, 0);
				coin->loadInfo(data[i], ',');
				this->coins->insert(coin);
			}
			section = SECTION_NONE;
		}
		else if (line == "<GoombaFrames>") {
			section = SECTION_GOOMBA_FRAMES;
			continue;
		}
		else if (line == "</GoombaFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
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
			for (size_t i = 0; i < data.size(); ++i) {
				Koopa* koopa = new Koopa(0, 0, 0, 0, 0, 0, 0);
				koopa->loadInfo(data[i], ',');
				koopas->insert(koopa);
			}
			section = SECTION_NONE;
		}
		else if (line == "<MusicBoxFrames>") {
			section = SECTION_MUSIC_BOX_FRAMES;
			continue;
		}
		else if (line == "</MusicBoxFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				MusicBox* musicBox = new MusicBox(0, 0, 0, 0, 0, 0);
				musicBox->loadInfo(data[i], ',');
				this->musicBoxes->push_back(musicBox);
			}
			section = SECTION_NONE;
		}
		else if (line == "<BoomerangBroFrames>") {
			section = SECTION_BOOMERANG_BRO_FRAMES;
			continue;
		}
		else if (line == "</BoomerangBroFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				BoomerangBro* boomerangBro = new BoomerangBro(0, 0, 0, 0, 0, 0, 0);
				boomerangBro->loadInfo(data[i], ',');
				boomerangBros->insert(boomerangBro);
			}
			section = SECTION_NONE;
		}
		else if (line == "<BossFrames>") {
			section = SECTION_BOSS_FRAMES;
			continue;
		}
		else if (line == "</BossFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				Boss* boss = new Boss(0, 0, 0, 0, Camera::getInstance()->getLimitX(), Camera::getInstance()->getLimitY(), 0);
				boss->loadInfo(data[i], ',');
				this->bosses->insert(boss);
			}
			section = SECTION_NONE;
		}
		else if (line == "<ItemFrames>") {
			section = SECTION_ITEM_FRAMES;
			continue;
		}
		else if (line == "</ItemFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				Item* item = new Item(0, 0, 0, 0, 0, 0, 0);
				item->loadInfo(data[i], ',');
				this->items->insert(item);
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
		case SECTION_BLOCK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GOLDEN_BRICK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GIFT_BRICK_FRAMES:
			data.push_back(line);
			break;
		case SECTION_COIN_FRAMES:
			data.push_back(line);
			break;
		case SECTION_GOOMBA_FRAMES:
			data.push_back(line);
			break;
		case SECTION_KOOPA_FRAMES:
			data.push_back(line);
			break;
		case SECTION_MUSIC_BOX_FRAMES:
			data.push_back(line);
			break;
		case SECTION_BOOMERANG_BRO_FRAMES:
			data.push_back(line);
			break;
		case SECTION_BOSS_FRAMES:
			data.push_back(line);
			break;
		case SECTION_ITEM_FRAMES:
			data.push_back(line);
		default:
			break;
		}
	}

	fs.close();
}

void ThirdVC::adaptAnimation()
{
	// Golden Bricks
	unordered_set<GoldenBrick*> ::iterator goldenBrickItr;
	for (goldenBrickItr = this->goldenBricks->begin(); goldenBrickItr != this->goldenBricks->end(); ++goldenBrickItr) {
		(*goldenBrickItr)->setState(GoldenBrickState::GOLDEN_BRICK_STAYING);
		if ((*goldenBrickItr)->getHasPButton()) {
			(*goldenBrickItr)->getPButton()->setState(PButtonState::PBUTTON_ON);
		}
	}

	// Gift Bricks
	for (size_t i = 0; i < this->giftBricks->size(); ++i) {
		this->giftBricks->at(i)->setState(GiftBrickState::FULLGIFTBRICK);
		if (this->giftBricks->at(i)->getGiftType() == SuperMushroomOrSuperLeaf) { // Super Mushroom, super leaf
			this->giftBricks->at(i)->getSuperMushroom()->setUpAnimation();
			this->giftBricks->at(i)->getSuperLeaf()->setAnimation(new Animation(AnimationBundle::getInstance()->getSuperLeaf()));

			this->giftBricks->at(i)->setSuperMushroomState(SuperMushroomState::SUPER_MUSHROOM_GROWING_UP);
			this->giftBricks->at(i)->setSuperLeafState(SuperLeafState::SUPER_LEAF_POPPING_UP);
		}
		else if (this->giftBricks->at(i)->getGiftType() == SuperMushroomGift) {
			this->giftBricks->at(i)->getSuperMushroom()->setUpAnimation();
			this->giftBricks->at(i)->setSuperMushroomState(SuperMushroomState::SUPER_MUSHROOM_GROWING_UP);
		}
	}

	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		(*coinItr)->setAnimation(new Animation(AnimationBundle::getInstance()->getCoin()));
	}


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
		//}
	}

	// Koopas
	unordered_set<Koopa*> ::iterator koopaItr;
	for (koopaItr = this->koopas->begin(); koopaItr != this->koopas->end(); ++koopaItr) {
		if ((*koopaItr)->getIsFlyingMode()) {
			if ((*koopaItr)->getVx() >= 0) {
				(*koopaItr)->setState(KoopaState::KOOPA_FLYING_RIGHT);
			}
			else if ((*koopaItr)->getVx() < 0) {
				(*koopaItr)->setState(KoopaState::KOOPA_FLYING_LEFT);
			}
		}
		else {
			if ((*koopaItr)->getVx() >= 0) {
				(*koopaItr)->setState(KoopaState::KOOPA_MOVING_RIGHT);
			}
			else if ((*koopaItr)->getVx() < 0) {
				(*koopaItr)->setState(KoopaState::KOOPA_MOVING_LEFT);
			}
		}
	}

	// Music Box
	for (size_t i = 0; i < this->musicBoxes->size(); ++i) {
		if (this->musicBoxes->at(i)->getIsSpecial()) {
			this->musicBoxes->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getMusicBoxRed()));
		}
		else {
			this->musicBoxes->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getMusicBox()));
		}
	}

	// Boomerang Bro
	unordered_set<BoomerangBro*> ::iterator boomerangBroItr;
	for (boomerangBroItr = this->boomerangBros->begin(); boomerangBroItr != this->boomerangBros->end(); ++boomerangBroItr) {
		if ((*boomerangBroItr)->getVx() < 0) {
			(*boomerangBroItr)->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_LEFT);
		}
		else {
			(*boomerangBroItr)->setState(BoomerangBroState::BOOMERANG_BRO_MOVING_RIGHT);
		}
		(*boomerangBroItr)->getFirstBoomerang()->setAnimation(new Animation(AnimationBundle::getInstance()->getBoomerang()));
		(*boomerangBroItr)->getSecondBoomerang()->setAnimation(new Animation(AnimationBundle::getInstance()->getBoomerang()));
	}

	// Boss
	unordered_set<Boss*> ::iterator bossItr;
	for (bossItr = this->bosses->begin(); bossItr != this->bosses->end(); ++bossItr) {
		if ((*bossItr)->getVx() < 0) {
			(*bossItr)->setState(BossState::BOSS_FLYING_TOP_LEFT);
		}
		else {
			(*bossItr)->setState(BossState::BOSS_FLYING_TOP_RIGHT);
		}

		(*bossItr)->getFirstBomb()->setAnimation(new Animation(AnimationBundle::getInstance()->getBomb()));
		(*bossItr)->getSecondBomb()->setAnimation(new Animation(AnimationBundle::getInstance()->getBomb()));
		(*bossItr)->getThirdBomb()->setAnimation(new Animation(AnimationBundle::getInstance()->getBomb()));
	}


	// Item
	unordered_set<Item*> ::iterator itemItr;
	for (itemItr = this->items->begin(); itemItr != this->items->end(); ++itemItr) {
		(*itemItr)->setAnimation(new Animation(AnimationBundle::getInstance()->getItems()));
	}

	this->mario->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
	this->mario->setState(MarioState::DROPPING);
	this->mario->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
	this->mario->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
}

void ThirdVC::adaptToGrid()
{
	// Grounds
	for (size_t i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}

	// Blocks
	for (size_t i = 0; i < this->blocks->size(); ++i) {
		Grid::getInstance()->add(this->blocks->at(i));
	}

	// Golden Bricks
	unordered_set<GoldenBrick*> ::iterator goldenBrickItr;
	for (goldenBrickItr = this->goldenBricks->begin(); goldenBrickItr != this->goldenBricks->end(); ++goldenBrickItr) {
		Grid::getInstance()->add(*goldenBrickItr);
	}

	// Gift Bricks
	for (size_t i = 0; i < this->giftBricks->size(); ++i) {
		Grid::getInstance()->add(this->giftBricks->at(i));
	}

	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		Grid::getInstance()->add(*coinItr);
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

	// Music Box
	for (size_t i = 0; i < this->musicBoxes->size(); ++i) {
		Grid::getInstance()->add(this->musicBoxes->at(i));
	}

	// Boomerang Bro
	unordered_set<BoomerangBro*> ::iterator boomerangBroItr;
	for (boomerangBroItr = this->boomerangBros->begin(); boomerangBroItr != this->boomerangBros->end(); ++boomerangBroItr) {
		Grid::getInstance()->add(*boomerangBroItr);
	}

	// Boss
	unordered_set<Boss*> ::iterator bossItr;
	for (bossItr = this->bosses->begin(); bossItr != this->bosses->end(); ++bossItr) {
		Grid::getInstance()->add(*bossItr);
	}


	// Item
	unordered_set<Item*> ::iterator itemItr;
	for (itemItr = this->items->begin(); itemItr != this->items->end(); ++itemItr) {
		Grid::getInstance()->add(*itemItr);
	}
}
