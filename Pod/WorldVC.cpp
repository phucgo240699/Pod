#include "WorldVC.h"

void WorldVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == enter) {
			if (wMario->getCurrentSceneId() == 'A') {
				Setting::getInstance()->isTransfering = true;
				Setting::getInstance()->setSceneName(SceneName::SunnyScene);
				return;
			}
		}
	}
	wMario->onKeyDown(_keyTypes);
}

void WorldVC::viewDidLoad()
{
	map = new WorldMap(ImagePath::getInstance()->world_map, D3DCOLOR_XRGB(255, 0, 255));
	grasses = new StaticAnim();
	helpLabel = new StaticAnim();
	wMario = new WMario(0, 0, 0, 0, 0, 0);
	scoreBoard = new ScoreBoard(ImagePath::getInstance()->board, D3DCOLOR_XRGB(255, 0, 255));

	this->adaptData();
}

void WorldVC::viewWillUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}

	if (grasses != NULL) {
		grasses->Update(_dt);
	}

	if (helpLabel != NULL) {
		helpLabel->Update(_dt);
	}

	if (scoreBoard != NULL) {
		scoreBoard->Update(_dt);
	}

	if (wMario != NULL) {
		wMario->Update(_dt);
	}
}

void WorldVC::viewDidRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}

		if (grasses != NULL) {
			grasses->Draw(map->getTexture());
		}

		if (helpLabel != NULL) {
			helpLabel->Draw(map->getTexture());
		}

		if (scoreBoard != NULL) {
			scoreBoard->Draw();
		}

		if (wMario != NULL) {
			wMario->Draw(map->getTexture());
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void WorldVC::adaptData()
{
	Camera* camera = Camera::getInstance();
	Setting* setting = Setting::getInstance();

	fstream fs;
	fs.open(FilePath::getInstance()->world_map, ios::in);

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
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<GrassAnimation>") {
			section = SECTION_GRASS_ANIMATION;
			continue;
		}
		else if (line == "</GrassAnimation>") {
			grasses->loadAnimation(data, '>', ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<GrassFrames>") {
			section = SECTION_GRASS_FRAMES;
			continue;
		}
		else if (line == "</GrassFrames>") {
			grasses->loadFrames(data, ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<HelpLabelAnimation>") {
			section = SECTION_HELP_LABEL_ANIMATION;
			continue;
		}
		else if (line == "</HelpLabelAnimation>") {
			helpLabel->loadAnimation(data, '>', ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<HelpLabelFrame>") {
			section = SECTION_HELP_LABEL_FRAME;
			continue;
		}
		else if (line == "</HelpLabelFrame>") {
			helpLabel->loadFrames(data, ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<WMarioInfo>") {
			section = SECTION_WMARIO_INFO;
			continue;
		}
		else if (line == "</WMarioInfo>") {
			section = SECTION_NONE;
		}
		else if (line == "<WMarioAnimation>") {
			section = SECTION_WMARIO_ANIMATION;
			continue;
		}
		else if (line == "</WMarioAnimation>") {
			wMario->loadAnimations(data, '>', ',');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<WMarioMovingMatrix>") {
			section = SECTION_WMARIO_MOVING_MATRIX;
			continue;
		}
		else if (line == "</WMarioMovingMatrix>") {
			wMario->loadMovingMatrix(data, ' ');
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
		case SECTION_GRASS_ANIMATION:
			data.push_back(line);
			break;
		case SECTION_GRASS_FRAMES:
			data.push_back(line);
			break;
		case SECTION_HELP_LABEL_ANIMATION:
			data.push_back(line);
			break;
		case SECTION_HELP_LABEL_FRAME:
			data.push_back(line);
			break;
		case SECTION_WMARIO_INFO:
			wMario->loadInfo(line, ',');
			break;
		case SECTION_WMARIO_ANIMATION:
			data.push_back(line);
			break;
		case SECTION_WMARIO_MOVING_MATRIX:
			data.push_back(line);
			break;
		case SECTION_SCORE_BOARD:
			scoreBoard->loadPosition(line, ',');
			break;
		default:
			break;
		}
	}

	fs.close();
}
