#include "SunnyVC.h"


//SunnyVC::~SunnyVC()
//{
//	delete mario;
//	delete map;
//
//	// Ground
//	for (int i = 0; i < this->grounds->size(); ++i) {
//		delete this->grounds->at(i);
//	}
//	delete this->grounds;
//
//	// Block
//	for (int i = 0; i < this->blocks->size(); ++i) {
//		delete this->blocks->at(i);
//	}
//	delete this->blocks;
//	
//	// Golden Brick
//	for (int i = 0; i < this->goldenBricks->size(); ++i) {
//		delete this->goldenBricks->at(i);
//	}
//	delete this->goldenBricks;
//
//	// Gift Brick
//	for (int i = 0; i < this->giftBricks->size(); ++i) {
//		delete this->giftBricks->at(i);
//	}
//	delete this->giftBricks;
//
//	// Green Pipe
//	for (int i = 0; i < this->greenPipes->size(); ++i) {
//		delete this->greenPipes->at(i);
//	}
//	delete this->greenPipes;
//
//	// Goomba
//	unordered_set<Goomba*> ::iterator itr;
//	for (itr = this->goombas->begin(); itr != this->goombas->end(); ++itr) {
//		delete (*itr);
//	}
//	delete this->goombas;
//}

void SunnyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new Map();
	grounds = new vector<Ground*>();
	goldenBricks = new unordered_set<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();
	greenPipes = new vector<GreenPipe*>();
	goombas = new unordered_set<Goomba*>();
	koopas = new unordered_set<Koopa*>();
	blocks = new vector<Block*>();
	fireFlowers = new unordered_set<FireFlower*>();
	flowers = new unordered_set<Flower*>();
	coins = new unordered_set<Coin*>();

	this->mario->load();

	this->adaptData();
	this->adaptAnimation();
}

void SunnyVC::viewReceiveKeyUp()
{
	//if (this->mario->getState() == DIE
	//	|| this->mario->getState() == DIE_JUMPING
	//	|| this->mario->getState() == DIE_DROPPING
	//	|| this->mario->getState() == SCALING_UP
	//	|| this->mario->getState() == SCALING_DOWN
	//	|| this->mario->getState() == TRANSFERING_TO_FLY) {
	//	return;
	//}
	mario->onKeyUp();
}

void SunnyVC::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	//if (this->mario->getState() == DIE
	//	|| this->mario->getState() == DIE_JUMPING
	//	|| this->mario->getState() == DIE_DROPPING
	//	|| this->mario->getState() == SCALING_UP
	//	|| this->mario->getState() == SCALING_DOWN
	//	|| this->mario->getState() == TRANSFERING_TO_FLY) {
	//	return;
	//}
	mario->onKeyUp(_keyTypes);
}

void SunnyVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	//if (this->mario->getState() == DIE
	//	|| this->mario->getState() == DIE_JUMPING
	//	|| this->mario->getState() == DIE_DROPPING
	//	|| this->mario->getState() == SCALING_UP
	//	|| this->mario->getState() == SCALING_DOWN
	//	|| this->mario->getState() == TRANSFERING_TO_FLY) {
	//	return;
	//}
	
	for (size_t i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::down
			&& this->mario->getComponentIdStandingOn() == this->componentIdToUnderground
			&& this->mario->getX() >= leftAnchorGreenPipeToPassThrough
			&& this->mario->getX() + this->mario->getBoundsWidth() <= rightAnchorGreenPipeToPassThrough) {
			this->mario->setState(MarioState::DROPPING_DOWN_PIPE);
			return;
		}
	}
	mario->onKeyDown(_keyTypes);
}

void SunnyVC::viewWillUpdate(float _dt)
{
	// Check by cell in grid
	unordered_set<Component*> cell;
	int beginRow = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRow = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginCol = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endCol = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));

	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			cell = Grid::getInstance()->getCell(i, j);

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


				// Fire Flower
				else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Fire Flower Ball
				else if (beginFireFlowerBallId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerBallId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Flower
				else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
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

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}

				// PButton
				else if (beginPButtonId <= (*itr)->getId() && (*itr)->getId() <= endPButtonId) {
					// Prevent update mullti time in one loop
					(*itr)->setIsUpdatedInOneLoop(false);
				}
			}
		}
	}
}

void SunnyVC::viewUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}

	// Check by cell in grid
	unordered_set<Component*> cell;
	int beginRow = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRow = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginCol = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endCol = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));
	for (int i = beginRow; i < endRow; ++i) {
		for (int j = beginCol; j < endCol; ++j) {

			if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

			cell = Grid::getInstance()->getCell(i, j);

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


				// Fire Flower
				else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->fireFlowers->erase(static_cast<FireFlower*>(*itr));
						continue;
					}

					if (static_cast<FireFlower*>(*itr)->getCountDown() % 12 == 0 &&
						(static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_STANDING_LOOK_UP || static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_STANDING_LOOK_DOWN)) {
						if (this->mario->getY() + this->mario->getBoundsHeight() > (*itr)->getY()) {
							static_cast<FireFlower*>(*itr)->setState(FireFlowerState::FIRE_FLOWER_STANDING_LOOK_DOWN);
						}
						else if ((static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_STANDING_LOOK_UP || static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_STANDING_LOOK_DOWN)
							&& this->mario->getY() < (*itr)->getY()) {
							static_cast<FireFlower*>(*itr)->setState(FireFlowerState::FIRE_FLOWER_STANDING_LOOK_UP);
						}
					}

					static_cast<FireFlower*>(*itr)->setIsFlip(this->mario->getX() <= (*itr)->getX() + (*itr)->getWidth());

					if ((static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_HIDING
						&& (static_cast<FireFlower*>(*itr)->getLeftAnchor() > this->mario->getX() + this->mario->getWidth()
							|| static_cast<FireFlower*>(*itr)->getRightAnchor() < this->mario->getX()
							|| static_cast<FireFlower*>(*itr)->getTopAnchor() > this->mario->getY() + this->mario->getHeight())
						)
						|| static_cast<FireFlower*>(*itr)->getState() != FIRE_FLOWER_HIDING) {

						//if () {
							(*itr)->Update(_dt);

							// update which cell in grid that it's belongs to
							Grid::getInstance()->updateCellOf(*itr);
						//}
					}
					else {
						static_cast<FireFlower*>(*itr)->reduceCountDown();
					}
				}

				// Fire Flower Ball
				else if (beginFireFlowerBallId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerBallId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					(*itr)->Update(_dt);

					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->isCollidingByFrame(Camera::getInstance()->getFrame()) == false) {
						Grid::getInstance()->remove(*itr, i, j);
						static_cast<FireBall*>(*itr)->setIsOutOfGrid(true);
					}
				}

				// Flower
				else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					if (static_cast<Flower*>(*itr)->getState() == FLOWER_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->flowers->erase(static_cast<Flower*>(*itr));
						continue;
					}

					if ((static_cast<Flower*>(*itr)->getState() == FLOWER_HIDING
						&& (static_cast<Flower*>(*itr)->getLeftAnchor() > this->mario->getX() + this->mario->getWidth()
							|| static_cast<Flower*>(*itr)->getRightAnchor() < this->mario->getX()
							|| static_cast<Flower*>(*itr)->getTopAnchor() > this->mario->getY() + this->mario->getHeight())
						)
						|| static_cast<Flower*>(*itr)->getState() != FLOWER_HIDING) {

						(*itr)->Update(_dt);

						// update which cell in grid that it's belongs to
						Grid::getInstance()->updateCellOf(*itr);
					}
					else {
						static_cast<Flower*>(*itr)->reduceCountDown();
					}
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

					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

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

				// PButton
				else if (beginPButtonId <= (*itr)->getId() && (*itr)->getId() <= endPButtonId) {
					// Prevent update mullti time in one loop
					if ((*itr)->getIsUpdatedInOneLoop()) continue;

					(*itr)->Update(_dt);
				}
			}
		}
	}

	if (mario != NULL) {
		mario->Update(_dt);

		if (this->mario->getState() == DROPPING_DOWN_PIPE) {
			if (this->mario->getY() >= this->mario->getEndDroppingDownPipe()) {
				this->navigateTo(SceneName::UndergroundScene);
				return;
			}
		}
		else if (this->mario->getState() == POPPING_UP_PIPE) {
			if (this->mario->getY() <= this->mario->getEndPoppingUpPipe()) {
				this->mario->setState(MarioState::STANDING);
				return;
			}
		}
		else {

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
	}

	AnimationCDPlayer::getInstance()->Update(_dt);
	
	// PButton
	if (this->getIsPressedPButton() && this->getIsRestoredGoldenBrick() == false) {
		if (this->countDownGoldenBrickBeingCoin <= 0) {
			unordered_set<GoldenBrick*> ::iterator goldenBrickItr;
			for (goldenBrickItr = this->goldenBricks->begin(); goldenBrickItr != this->goldenBricks->end(); ++goldenBrickItr) {
				if ((*goldenBrickItr)->getState() == GOLDEN_BRICK_BEING_COIN) {
					(*goldenBrickItr)->setState(GoldenBrickState::GOLDEN_BRICK_STAYING);
				}
			}
			this->setIsRestoredGoldenBrick(true);
		}
		if (this->isRestoredCamera == false) {
			if (this->countDownGoldenBrickBeingCoin >= 320) {
				if (this->countDownGoldenBrickBeingCoin % 2 == 0 || this->countDownGoldenBrickBeingCoin % 3 == 0) {
					Camera::getInstance()->plusX(camShakingValue);
					camShakingValue *= -1;
				}
			}
			else {
				this->isRestoredCamera = true;
			}
		}
		--countDownGoldenBrickBeingCoin;
	}

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

void SunnyVC::viewDidUpdate(float _dt)
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
	int beginRowMario = int(floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()));
	int endRowMario = int(ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()));
	int beginColMario = int(floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()));
	int endColMario = int(ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()));
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

				// Gift Brick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					this->mario->handleGiftBrickCollision(static_cast<GiftBrick*>(*itr), _dt);
				}

				// Green Pipe
				else if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
					this->mario->handleGreenPipeCollision(static_cast<GreenPipe*>(*itr), _dt);
				}

				/*if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY)
				{
					continue;
				}*/

				// Fire Flower
				else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
					if (this->mario->getIsFlashMode() == false) {
						this->mario->handleFireFlowerCollision(static_cast<FireFlower*>(*itr), _dt);
						static_cast<FireFlower*>(*itr)->handleMarioCollision(this->mario, _dt);
					}

					static_cast<FireFlower*>(*itr)->handleFireBallCollision(this->mario->getFirstFireBall(), _dt);
				}

				// Fire Flower Ball
				else if (beginFireFlowerBallId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerBallId) {
					if (this->mario->getIsFlashMode() == false) {
						this->mario->handleFireFlowerBallCollision(static_cast<FireFlowerBall*>(*itr), _dt);
						static_cast<FireFlowerBall*>(*itr)->handleMarioCollision(this->mario, _dt);
					}
				}

				// Flower
				else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
					if (this->mario->getIsFlashMode() == false) {
						this->mario->handleFlowerCollision(static_cast<Flower*>(*itr), _dt);
						static_cast<Flower*>(*itr)->handleMarioCollision(this->mario, _dt);
					}

					static_cast<Flower*>(*itr)->handleFireBallCollsion(this->mario->getFirstFireBall(), _dt);
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
									|| (beginGreenPipeId <= (*superMushroomItr)->getId() && (*superMushroomItr)->getId() <= endGreenPipeId)) {
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
									|| (beginGreenPipeId <= (*goombaItr)->getId() && (*goombaItr)->getId() <= endGreenPipeId)) {
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
									|| (beginGreenPipeId <= (*koopaItr)->getId() && (*koopaItr)->getId() <= endGreenPipeId)) {
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
							}
						}
					}

					if (static_cast<Koopa*>(*itr)->getIsStandOnSurface() == false && static_cast<Koopa*>(*itr)->getIsOutOfFirstStage() && static_cast<Koopa*>(*itr)->getState() != KOOPA_FLYING_LEFT && static_cast<Koopa*>(*itr)->getState() != KOOPA_FLYING_RIGHT) {
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
								if ((beginGroundId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGroundId)
									|| (beginGreenPipeId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGreenPipeId)) {
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
								else if (beginFireFlowerId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endFireFlowerId) {
									static_cast<FireBall*>(*itr)->handleFireFlowerCollision(static_cast<FireFlower*>(*fireBallItr), _dt);
								}
								else if (beginFlowerId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endFlowerId) {
									static_cast<FireBall*>(*itr)->handleFlowerCollision(static_cast<Flower*>(*fireBallItr), _dt);
								}
								else if (beginGoldenBrickId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGoldenBrickId) {
									static_cast<FireBall*>(*itr)->handleGoldenBrickCollision(static_cast<GoldenBrick*>(*fireBallItr), _dt);
								}
							}
						}
					}
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					this->mario->handleCoinCollision(static_cast<Coin*>(*itr), _dt);
					static_cast<Coin*>(*itr)->handleMarioCollision(this->mario, _dt);
				}

				// PButton
				else if (beginPButtonId <= (*itr)->getId() && (*itr)->getId() <= endPButtonId) {
					this->mario->handlePButtonCollision(static_cast<PButton*>(*itr), _dt);

					if (this->getIsPressedPButton() == false && static_cast<PButton*>(*itr)->getState() == PBUTTON_OFF) {
						this->setIsPressedPButton(true);
						countDownGoldenBrickBeingCoin = 340;

						unordered_set<GoldenBrick*> ::iterator goldenBrickItr;
						for (goldenBrickItr = this->goldenBricks->begin(); goldenBrickItr != this->goldenBricks->end(); ++goldenBrickItr) {
							if ((*goldenBrickItr)->getState() == GOLDEN_BRICK_STAYING) {
								(*goldenBrickItr)->setState(GoldenBrickState::GOLDEN_BRICK_BEING_COIN);
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

void SunnyVC::viewWillRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw(Drawing::getInstance()->getSunnyMapTexture());
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

					// Super Mushroom
					else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// SuperLeaf
					else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Fire Flower
					else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
						if ((static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_HIDING
							&& (static_cast<FireFlower*>(*itr)->getLeftAnchor() > this->mario->getX() + this->mario->getWidth()
								|| static_cast<FireFlower*>(*itr)->getRightAnchor() < this->mario->getX()
								|| static_cast<FireFlower*>(*itr)->getTopAnchor() > this->mario->getY() + this->mario->getHeight())
							)
							|| static_cast<FireFlower*>(*itr)->getState() != FIRE_FLOWER_HIDING) {
								(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
						}
					}

					// Flower
					else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
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

					// Coin
					else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// PButton
					else if (beginPButtonId <= (*itr)->getId() && (*itr)->getId() <= endPButtonId) {
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

					// Gift Brick
					if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
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
					// Green Pipe
					if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
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
					
					// Fire Flower Ball
					if (beginFireFlowerBallId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerBallId) {
						(*itr)->Draw(Drawing::getInstance()->getSunnyMapTexture());
					}

					// Fire Ball
					else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
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

bool SunnyVC::getIsPressedPButton()
{
	return this->isPressedPButton;
}

bool SunnyVC::getIsRestoredGoldenBrick()
{
	return this->isRestoredGoldenBrick;
}

Mario* SunnyVC::getMario()
{
	return this->mario;
}

void SunnyVC::setIsPressedPButton(bool _isPressedPButton)
{
	this->isPressedPButton = _isPressedPButton;
}

void SunnyVC::setIsRestoredGoldenBrick(bool _isRestoreGoldenBrick)
{
	this->isRestoredGoldenBrick = _isRestoreGoldenBrick;
}

void SunnyVC::viewDidRender()
{
}

void SunnyVC::setMario(Mario* _mario)
{
	this->mario = _mario;
}

float SunnyVC::getLeftAnchorMarioPoppingUpFromPipe()
{
	return this->leftAnchorMarioPoppingUpFromPipe;
}

float SunnyVC::getBottomAnchorMarioPoppingUpFromPipe()
{
	return this->bottomAnchorMarioPoppingUpFromPipe;
}

void SunnyVC::viewWillRelease()
{
}

void SunnyVC::adaptRangeID(vector<string> data, char seperator)
{
	vector<int> v;
	for (size_t i = 0; i < data.size(); ++i) {
		if (i == 4) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGroundId = v[0];
			this->endGroundId = v[1];
		}
		else if (i == 5) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginBlockId = v[0];
			this->endBlockId = v[1];
		}
		else if (i == 6) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGoldenBrickId = v[0];
			this->endGoldenBrickId = v[1];
		}
		else if (i == 0) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginSuperMushroomId = v[0];
			this->endSuperMushroomId = v[1];
		}
		else if (i == 9) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginSuperLeafId = v[0];
			this->endSuperLeafId = v[1];
		}
		else if (i == 3) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGiftBrickId = v[0];
			this->endGiftBrickId = v[1];
		}
		else if (i == 7) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginFireFlowerId = v[0];
			this->endFireFlowerId = v[1];
			this->beginFlowerId = v[2];
			this->endFlowerId = v[3];
		}
		else if (i == 8) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGreenPipeId = v[0];
			this->endGreenPipeId = v[1];
			this->componentIdToUnderground = v[2];
			this->leftAnchorGreenPipeToPassThrough = v[3];
			this->rightAnchorGreenPipeToPassThrough = v[4];
			this->leftAnchorMarioPoppingUpFromPipe = float(v[5]);
			this->bottomAnchorMarioPoppingUpFromPipe = float(v[6]);
		}
		else if (i == 1) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginGoombaId = v[0];
			this->endGoombaId = v[1];
		}
		else if (i == 2) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginKoopaId = v[0];
			this->endKoopaId = v[1];
		}
		else if (i == 10) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginFireBallId = v[0];
			this->endFireBallId = v[1];
			this->beginFireFlowerBallId = v[2];
			this->endFireFlowerBallId = v[3];
		}
		else if (i == 11) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginCoinId = v[0];
			this->endCoinId = v[1];
		}
		else if (i == 12) {
			v = Tool::splitToVectorIntegerFrom(data[i], seperator);
			this->beginPButtonId = v[0];
			this->endPButtonId = v[1];
		}
	}
}

void SunnyVC::adaptData()
{
	//Camera* camera = Camera::getInstance();

	fstream fs;
	fs.open(FilePath::getInstance()->sunny_map, ios::in);

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
		else if (line == "<GreenPipeFrames>") {
			section = SECTION_GREEN_PIPE_FRAMES;
			continue;
		}
		else if (line == "</GreenPipeFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
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
		else if (line == "<FireFlowerFrames>") {
			section = SECTION_FIRE_FLOWER_FRAMES;
			continue;
		}
		else if (line == "</FireFlowerFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				FireFlower* fireFlower = new FireFlower(0, 0, 0, 0, 0, 0, 0);
				fireFlower->loadInfo(data[i], ',');
				fireFlowers->insert(fireFlower);
			}
			section = SECTION_NONE;
		}
		else if (line == "<FlowerFrames>") {
			section = SECTION_FLOWER_FRAMES;
			continue;
		}
		else if (line == "</FlowerFrames>") {
			for (size_t i = 0; i < data.size(); ++i) {
				Flower* flower = new Flower(0, 0, 0, 0, 0, 0, 0);
				flower->loadInfo(data[i], ',');
				flowers->insert(flower);
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
		/*else if (line == "<GridInfo>") {
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
		}*/
		/*else if (line == "<AnimationBundle>") {
			section = SECTION_ANIMATION_BUNDLE;
			continue;
		}
		else if (line == "</AnimationBundle>") {
			AnimationBundle::getInstance()->loadAnimations(data, '>', ',');
			section = SECTION_NONE;
		}*/

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
		case SECTION_FIRE_FLOWER_FRAMES:
			data.push_back(line);
			break;
		case SECTION_FLOWER_FRAMES:
			data.push_back(line);
			break;
		case SECTION_COIN_FRAMES:
			data.push_back(line);
			break;
		//case SECTION_GRID_INFO:
		//	Grid::getInstance()->loadInfo(line, ',');
		//	break;
		//case SECTION_GRID_MATRIX_ID:
		//	data.push_back(line);
		//	break;
		/*case SECTION_ANIMATION_BUNDLE:
			data.push_back(line);
			break;*/
		default:
			break;
		}
	}

	fs.close();
}

void SunnyVC::adaptAnimation()
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

	// Green Pipes
	for (size_t i = 0; i < this->greenPipes->size(); ++i) {
		if (this->greenPipes->at(i)->getFloorNumber() == 2) {
			this->greenPipes->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getGreenPipe2Floor()));
		}
		else {
			this->greenPipes->at(i)->setAnimation(new Animation(AnimationBundle::getInstance()->getGreenPipe3Floor()));
		}
	}

	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		(*coinItr)->setAnimation(new Animation(AnimationBundle::getInstance()->getCoin()));
	}



	///
	/// --------------------------- Enemies ---------------------------
	///

	// Fire Flowers
	unordered_set<FireFlower*> ::iterator fireFlowerItr;
	for (fireFlowerItr = this->fireFlowers->begin(); fireFlowerItr != this->fireFlowers->end(); ++fireFlowerItr) {
		(*fireFlowerItr)->setState(FireFlowerState::FIRE_FLOWER_HIDING);
		(*fireFlowerItr)->setFireFlowerBallState(FireFlowerBallState::FIRE_FLOWER_BALL_FLYING_STAYING);
		(*fireFlowerItr)->setFireFlowerBallAnimation(new Animation(AnimationBundle::getInstance()->getFireFlowerBall()));
	}

	// Flowers
	unordered_set<Flower*> ::iterator flowerItr;
	for (flowerItr = this->flowers->begin(); flowerItr != this->flowers->end(); ++flowerItr) {
		(*flowerItr)->setState(FlowerState::FLOWER_HIDING);
	}

	// Goombas
	unordered_set<Goomba*> ::iterator goombaItr;
	for (goombaItr = this->goombas->begin(); goombaItr != this->goombas->end(); ++goombaItr) {
		/*if ((*goombaItr)->getIsFlyingMode()) {
			if ((*goombaItr)->getVx() > 0) {
				(*goombaItr)->setState(GoombaState::GOOMBA_POPPING_RIGHT);
			}
			else if ((*goombaItr)->getVx() < 0) {
				(*goombaItr)->setState(GoombaState::GOOMBA_POPPING_LEFT);
			}
			else {
				(*goombaItr)->setState(GoombaState::GOOMBA_STANDING);
			}
		}
		else {*/
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

	this->mario->setAnimation(new Animation(AnimationBundle::getInstance()->getMarioStanding()));
	this->mario->setState(MarioState::DROPPING);
	this->mario->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
	this->mario->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
}

void SunnyVC::adaptToGrid()
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

	// Green Pipes
	for (size_t i = 0; i < this->greenPipes->size(); ++i) {
		Grid::getInstance()->add(this->greenPipes->at(i));
	}

	// Fire Flowers
	unordered_set<FireFlower*> ::iterator fireFlowerItr;
	for (fireFlowerItr = this->fireFlowers->begin(); fireFlowerItr != this->fireFlowers->end(); ++fireFlowerItr) {
		Grid::getInstance()->add(*fireFlowerItr);
		//Grid::getInstance()->add(this->fireFlowers->at(i)->getFireFlowerBall());
	}

	// Flowers
	unordered_set<Flower*> ::iterator flowerItr;
	for (flowerItr = this->flowers->begin(); flowerItr != this->flowers->end(); ++flowerItr) {
		Grid::getInstance()->add(*flowerItr);
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
}
