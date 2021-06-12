#include "SunnyVC.h"

void SunnyVC::viewDidLoad()
{
	mario = new Mario(0, 0, 0, 0, 0, 0, ImagePath::getInstance()->mario, D3DCOLOR_XRGB(255, 0, 255), DROPPING);
	map = new SunnyMap(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	grounds = new vector<Ground*>();
	giftBrick = new GiftBrick(0,0,0,0,0,0);
	scoreBoard = new ScoreBoard(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));
	goldenBrickAnim = new StaticAnim();

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
	
	if (giftBrick != NULL) {
		giftBrick->Update(_dt);
	}
	if (goldenBrickAnim != NULL) {
		goldenBrickAnim->Update(_dt);
	}
	if (scoreBoard != NULL) {
		scoreBoard->Update(_dt);
	}
	if (mario != NULL) {
		mario->Update(_dt);
		Camera::getInstance()->follow(mario, _dt);
	}
}

void SunnyVC::viewDidUpdate(float _dt)
{

	// Check by cell in grid
	int startRow = floor(Camera::getInstance()->getY() / Grid::getInstance()->getCellHeight());
	int endRow = ceil((Camera::getInstance()->getY() + Camera::getInstance()->getHeight()) / Grid::getInstance()->getCellHeight());
	int startCol = floor(Camera::getInstance()->getX() / Grid::getInstance()->getCellWidth());
	int endCol = ceil((Camera::getInstance()->getX() + Camera::getInstance()->getWidth()) / Grid::getInstance()->getCellWidth());
	for (int i = startRow; i < endRow; ++i) {
		for (int j = startCol; j < endCol; ++j) {
			if (Grid::getInstance()->getCells()[i][j].size() == 0) continue;

			unordered_set<Component*> components = Grid::getInstance()->getCells()[i][j];
			unordered_set<Component*> ::iterator itr;
			for (itr = components.begin(); itr != components.end(); ++itr) {
				if ((*itr)->getId() == 0) {
					this->handleMarioGroundCollision((*itr), _dt);
				}
			}
		}
	}

	//// Collision: MainCharacter and Ground
	//for (int i = 0; i < this->grounds->size(); ++i) {
	//	
	//		mario_ground_collision = this->mario->sweptAABB(this->grounds->at(i), _dt);
	//		if (get<0>(mario_ground_collision) == true) {
	//			for (int j = 0; j < get<2>(mario_ground_collision).size(); ++j) {
	//				CollisionEdge edge = get<2>(mario_ground_collision)[j];
	//				if (edge == topEdge) {
	//					currentGroundIndex = i;
	//					mario->setY(this->grounds->at(i)->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
	//					mario->setState(MarioState::STANDING);
	//				}
	//				else if (edge == bottomEdge) {
	//					currentGroundIndex = i;
	//					mario->setY(this->grounds->at(i)->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
	//					mario->setState(MarioState::STANDING);
	//				}
	//				else if (edge == leftEdge) {
	//					mario->setSubState(MarioSubState::PUSHING);
	//				}
	//				else if (edge == rightEdge) {
	//					mario->setSubState(MarioSubState::PUSHING);
	//				}
	//			}
	//		}
	//		else {
	//			// if mario walk out of ground top surface, it will drop
	//			if (mario->getState() == WALKING || mario->getState() == STANDING) {
	//				if (mario->getBounds().right < this->grounds->at(currentGroundIndex)->getX() || mario->getX() > this->grounds->at(currentGroundIndex)->getBounds().right) { // this is check which ground that mario is standing on
	//					if (mario->getBounds().bottom <= this->grounds->at(currentGroundIndex)->getY()) {
	//						mario->setState(MarioState::DROPPING);
	//					}
	//				}
	//				//mario->setState(MarioState::DROPPING);
	//			}
	//		}
	//	
	//}
}

void SunnyVC::viewWillRender()
{
}

void SunnyVC::viewDidRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}
		if (giftBrick != NULL) {
			giftBrick->Draw(map->getTexture());
		}
		if (goldenBrickAnim != NULL) {
			goldenBrickAnim->Draw(map->getTexture());
		}
		if (mario != NULL) {
			mario->Draw();
		}

		if (scoreBoard != NULL) {
			scoreBoard->Draw();
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
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
		else if (line == "<GiftBrickFrames>") {
			section = SECTION_GIFT_BRICK_FRAMES;
			continue;
		}
		else if (line == "</GiftBrickFrames>") {
			section = SECTION_NONE;
		}
		else if (line == "<GiftBrickAnimation>") {
			section = SECTION_GIFT_BRICK_ANIMATION;
			continue;
		}
		else if (line == "</GiftBrickAnimation>") {
			giftBrick->loadAnimation(data);
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<ScoreBoard>") {
			section = SECTION_SCORE_BOARD;
			continue;
		}
		else if (line == "</ScoreBoard>") {
			section = SECTION_NONE;
		}
		else if (line == "<GoldenBrickAnimation>") {
			section = SECTION_GIFT_BRICK_ANIMATION;
			continue;
		}
		else if (line == "</GoldenBrickAnimation>") {
			goldenBrickAnim->loadAnimation(data, '>', ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<GoldenBrickFrames>") {
			section = SECTION_GOLDEN_BRICK_FRAMES;
			continue;
		}
		else if (line == "</GoldenBrickFrames>") {
			goldenBrickAnim->loadFrames(data, ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<GridInfo>") {
			section = SECTION_GRID_INFO;
			continue;
		}
		else if (line == "</GridInfo>") {
			section = SECTION_NONE;
		}

		switch (section)
		{
		case SECTION_NONE:
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
			giftBrick->loadInfo(line, ',');
			break;
		case SECTION_GIFT_BRICK_ANIMATION:
			data.push_back(line);
			break;
		case SECTION_SCORE_BOARD:
			scoreBoard->loadPosition(line, ',');
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
		default:
			break;
		}
	}

	fs.close();
}

void SunnyVC::adaptToGrid()
{
	for (int i = 0; i < this->grounds->size(); ++i) {
		Grid::getInstance()->add(this->grounds->at(i));
	}
}

void SunnyVC::handleMarioGroundCollision(Component* _ground, float _dt)
{
	mario_ground_collision = this->mario->sweptAABB(_ground, _dt);
	if (get<0>(mario_ground_collision) == true) {
		for (int j = 0; j < get<2>(mario_ground_collision).size(); ++j) {
			CollisionEdge edge = get<2>(mario_ground_collision)[j];
			if (edge == topEdge) {
				mario->setY(_ground->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
				mario->setState(MarioState::STANDING);
			}
			else if (edge == bottomEdge) {
				mario->setY(_ground->getY() - mario->getCurrentAnimation()->getCurrentFrameHeight());
				mario->setState(MarioState::STANDING);
			}
			else if (edge == leftEdge) {
				mario->setSubState(MarioSubState::PUSHING);
			}
			else if (edge == rightEdge) {
				mario->setSubState(MarioSubState::PUSHING);
			}
		}
	}
	//else {
	//	// if mario walk out of ground top surface, it will drop
	//	if (mario->getState() == WALKING || mario->getState() == STANDING) {
	//		if (mario->getBounds().right < this->grounds->at(currentGroundIndex)->getX() || mario->getX() > this->grounds->at(currentGroundIndex)->getBounds().right) { // this is check which ground that mario is standing on
	//			if (mario->getBounds().bottom <= this->grounds->at(currentGroundIndex)->getY()) {
	//				mario->setState(MarioState::DROPPING);
	//			}
	//		}
	//		//mario->setState(MarioState::DROPPING);
	//	}
	//}
}
