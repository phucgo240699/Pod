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
	map = new SunnyMap(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();
	goldenBricks = new vector<GoldenBrick*>();
	giftBricks = new vector<GiftBrick*>();
	greenPipes = new vector<GreenPipe*>();
	goombas = new unordered_set<Goomba*>();
	koopas = new unordered_set<Koopa*>();
	blocks = new vector<Block*>();
	fireFlowers = new unordered_set<FireFlower*>();
	flowers = new unordered_set<Flower*>();
	coins = new unordered_set<Coin*>();

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
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getState() == TRANSFERING_TO_FLY) {
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
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getState() == TRANSFERING_TO_FLY) {
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
		|| this->mario->getState() == SCALING_DOWN
		|| this->mario->getState() == TRANSFERING_TO_FLY) {
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
					/*if ((*itr)->getId() < beginGiftBrickId || (*itr)->getId() > endGiftBrickId) continue;*/
				if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					//if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP) {
						(*itr)->Update(_dt);
					//}
				}

				// Golden Brick
				if (beginGoldenBrickId <= (*itr)->getId() && (*itr)->getId() <= endGoldenBrickId) {
					if (static_cast<GoldenBrick*>(*itr)->getState() == GOLDEN_BRICK_DISAPPEARED) {
						Grid::getInstance()->remove(*itr, i, j);
					}
					(*itr)->Update(_dt);
				}

				// GiftBrick
				else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
					(*itr)->Update(_dt);
				}

				// SuperMushroom
				else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
					if (static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_DISAPPEARED
						|| static_cast<SuperMushroom*>(*itr)->getState() == SUPER_MUSHROOM_BEING_EARNED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY) {
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);
				}


				// ==========================================================================================
				if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN || this->mario->getState() == TRANSFERING_TO_FLY) {
					continue;
				}

				// SuperLeaf
				else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
					if (static_cast<SuperLeaf*>(*itr)->getState() == SUPER_LEAF_BEING_EARNED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}
					
					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);
				}

				// Fire Flower
				else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
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
					(*itr)->Update(_dt);

					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->isCollidingByFrame(Camera::getInstance()->getFrame()) == false) {
						Grid::getInstance()->remove(*itr, i, j);
						static_cast<FireBall*>(*itr)->setIsOutOfGrid(true);
					}
				}

				// Flower
				else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
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
					if (static_cast<Goomba*>(*itr)->getState() == DEAD_GOOMBA) {
						Grid::getInstance()->remove(*itr, i, j);
						this->goombas->erase(static_cast<Goomba*>(*itr));
						continue;
					}


					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);

					if ((*itr)->getY() + (*itr)->getHeight() > Camera::getInstance()->getLimitY()) {
						Grid::getInstance()->remove(*itr, i, j);
					}
				}

				// Koopas
				else if (beginKoopaId <= (*itr)->getId() && (*itr)->getId() <= endKoopaId) {
					if (static_cast<Koopa*>(*itr)->getState() == KOOPA_DEAD) {
						Grid::getInstance()->remove(*itr, i, j);
						this->koopas->erase(static_cast<Koopa*>(*itr));
						continue;
					}

					(*itr)->Update(_dt);

					// update which cell in grid that it's belongs to
					Grid::getInstance()->updateCellOf(*itr);
				}

				// Fire Ball
				else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
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
					if (static_cast<Coin*>(*itr)->getState() == COIN_BEING_EARNED) {
						Grid::getInstance()->remove(*itr, i, j);
						continue;
					}

					(*itr)->Update(_dt);

					Grid::getInstance()->updateCellOf(*itr);
				}
			}
		}
	}

	if (mario != NULL) {
		mario->Update(_dt);
		Camera::getInstance()->follow(mario, _dt);
	}

	AnimationCDPlayer::getInstance()->Update(_dt);

	if (this->mario->getState() == DIE || this->mario->getState() == DIE_JUMPING || this->mario->getState() == DIE_DROPPING || this->mario->getState() == SCALING_UP || this->mario->getState() == SCALING_DOWN) {
		return;
	}
	ScoreBoard::getInstance()->Update(_dt);
	ScoreBoard::getInstance()->setMomentumLevel(this->mario->getMomentumLevelToFly());
}

void SunnyVC::viewDidUpdate(float _dt)
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
					int beginRowSuperMushroom = floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int endRowSuperMushroom = ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int beginColSuperMushroom = floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());
					int endColSuperMushroom = ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());

					beginRowSuperMushroom = beginRowSuperMushroom < 0 ? 0 : beginRowSuperMushroom;
					endRowSuperMushroom = endRowSuperMushroom > Grid::getInstance()->getTotalRows() ? Grid::getInstance()->getTotalRows() : endRowSuperMushroom;
					beginColSuperMushroom = beginColSuperMushroom < 0 ? 0 : beginColSuperMushroom;
					endColSuperMushroom = endColSuperMushroom > Grid::getInstance()->getTotalCols() ? Grid::getInstance()->getTotalCols() : endColSuperMushroom;

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
					int beginRowKoopa = floor(((*itr)->getY() - (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int endRowKoopa = ceil(((*itr)->getY() + (*itr)->getHeight() + (Camera::getInstance()->getHeight() / 2)) / Grid::getInstance()->getCellHeight());
					int beginColKoopa = floor(((*itr)->getX() - (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());
					int endColKoopa = ceil(((*itr)->getX() + (*itr)->getWidth() + (Camera::getInstance()->getWidth() / 2)) / Grid::getInstance()->getCellWidth());

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
							}
						}
					}

					if (static_cast<Koopa*>(*itr)->getIsStandOnSurface() == false) {
						if (static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_LEFT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_LEFT);
						}
						else if (static_cast<Koopa*>(*itr)->getState() == KOOPA_SHRINKAGE_MOVING_RIGHT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_SHRINKAGE_DROPPING_RIGHT);
						}
						else if (static_cast<Koopa*>(*itr)->getIsGreenMode() && static_cast<Koopa*>(*itr)->getState() == KOOPA_MOVING_LEFT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_DROPPING_LEFT);
						}
						else if (static_cast<Koopa*>(*itr)->getIsGreenMode() && static_cast<Koopa*>(*itr)->getState() == KOOPA_MOVING_RIGHT) {
							static_cast<Koopa*>(*itr)->setState(KoopaState::KOOPA_DROPPING_RIGHT);
						}
					}

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

					for (int r = beginRowFireball; r < endRowFireball; ++r) {
						for (int c = beginColFireball; c < endColFireball; ++c) {
							unordered_set<Component*> fireBallCell = Grid::getInstance()->getCell(r, c);
							unordered_set<Component*> ::iterator fireBallItr;

							for (fireBallItr = fireBallCell.begin(); fireBallItr != fireBallCell.end(); ++fireBallItr) {
								if ((beginGroundId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGroundId)
									|| (beginGoldenBrickId <= (*fireBallItr)->getId() && (*fireBallItr)->getId() <= endGoldenBrickId)
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
							}
						}
					}
				}

				// Coin
				else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
					this->mario->handleCoinCollision(static_cast<Coin*>(*itr), _dt);
					static_cast<Coin*>(*itr)->handleMarioCollision(this->mario, _dt);
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
					else if (beginSuperMushroomId <= (*itr)->getId() && (*itr)->getId() <= endSuperMushroomId) {
						(*itr)->Draw(map->getTexture());
					}

					// SuperLeaf
					else if (beginSuperLeafId <= (*itr)->getId() && (*itr)->getId() <= endSuperLeafId) {
						(*itr)->Draw(map->getTexture());
					}

					// Gift Brick
					else if (beginGiftBrickId <= (*itr)->getId() && (*itr)->getId() <= endGiftBrickId) {
						(*itr)->Draw(map->getTexture());
					}

					// Fire Flower
					else if (beginFireFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerId) {
						if ((static_cast<FireFlower*>(*itr)->getState() == FIRE_FLOWER_HIDING
							&& (static_cast<FireFlower*>(*itr)->getLeftAnchor() > this->mario->getX() + this->mario->getWidth()
								|| static_cast<FireFlower*>(*itr)->getRightAnchor() < this->mario->getX()
								|| static_cast<FireFlower*>(*itr)->getTopAnchor() > this->mario->getY() + this->mario->getHeight())
							)
							|| static_cast<FireFlower*>(*itr)->getState() != FIRE_FLOWER_HIDING) {
								(*itr)->Draw(map->getTexture());
						}
					}

					// Fire Flower Ball
					else if (beginFireFlowerBallId <= (*itr)->getId() && (*itr)->getId() <= endFireFlowerBallId) {
						(*itr)->Draw(map->getTexture());
					}

					// Flower
					else if (beginFlowerId <= (*itr)->getId() && (*itr)->getId() <= endFlowerId) {
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

					// Fire Ball
					else if (beginFireBallId <= (*itr)->getId() && (*itr)->getId() <= endFireBallId) {
						(*itr)->Draw(map->getTexture());
					}

					// Coin
					else if (beginCoinId <= (*itr)->getId() && (*itr)->getId() <= endCoinId) {
						(*itr)->Draw(map->getTexture());
					}
				}
			}
		}

		for (int i = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight()); i < ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight()); ++i) {
			for (int j = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth()); j < ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth()); ++j) {
				if (Grid::getInstance()->getCell(i, j).size() == 0) continue;

				unordered_set<Component*> cell = Grid::getInstance()->getCell(i, j);
				unordered_set<Component*> ::iterator itr;
				for (itr = cell.begin(); itr != cell.end(); ++itr) {
					// Green Pipe
					if (beginGreenPipeId <= (*itr)->getId() && (*itr)->getId() <= endGreenPipeId) {
						(*itr)->Draw(map->getTexture());
					}
				}
			}
		}

		if (mario != NULL) {
			mario->Draw();
		}

		AnimationCDPlayer::getInstance()->Draw(map->getTexture());

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
		else if (line == "<FireFlowerFrames>") {
			section = SECTION_FIRE_FLOWER_FRAMES;
			continue;
		}
		else if (line == "</FireFlowerFrames>") {
			for (int i = 0; i < data.size(); ++i) {
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
			for (int i = 0; i < data.size(); ++i) {
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
			for (int i = 0; i < data.size(); ++i) {
				Coin* coin = new Coin(0, 0, 0, 0, 0, 0, 0, 0);
				coin->loadInfo(data[i], ',');
				this->coins->insert(coin);
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
		case SECTION_FIRE_FLOWER_FRAMES:
			data.push_back(line);
			break;
		case SECTION_FLOWER_FRAMES:
			data.push_back(line);
			break;
		case SECTION_COIN_FRAMES:
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
		if (this->giftBricks->at(i)->getGiftType() == NotPoint) { // Super Mushroom, super leaf
			this->giftBricks->at(i)->getSuperMushroom()->setAnimation(new Animation(AnimationBundle::getInstance()->getSuperMushroom()));
			this->giftBricks->at(i)->getSuperLeaf()->setAnimation(new Animation(AnimationBundle::getInstance()->getSuperLeaf()));

			this->giftBricks->at(i)->setSuperMushroomState(SuperMushroomState::SUPER_MUSHROOM_GROWING_UP);
			this->giftBricks->at(i)->setSuperLeafState(SuperLeafState::SUPER_LEAF_POPPING_UP);
		}
	}

	// Green Pipes
	for (int i = 0; i < this->greenPipes->size(); ++i) {
		this->greenPipes->at(i)->setupAnimation();
	}

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

	// Coins
	unordered_set<Coin*> ::iterator coinItr;
	for (coinItr = this->coins->begin(); coinItr != this->coins->end(); ++coinItr) {
		(*coinItr)->setAnimation(new Animation(AnimationBundle::getInstance()->getCoin()));
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
	this->mario->setFirstFireBallState(FireBallState::FIREBALL_STAYING);
	this->mario->setFirstFireBallAnimation(new Animation(AnimationBundle::getInstance()->getFireBall()));
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