#include "WorldVC.h"

//WorldVC::~WorldVC()
//{
//	delete map;
//	delete grasses;
//	delete helpLabel;
//	delete wMario;
//	delete wTurtle;
//}

void WorldVC::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == enter) {
			if (wMario->getCurrentSceneId() == '1') {
				/*Setting::getInstance()->setIsTransfering(true);
				Setting::getInstance()->setSceneName(SceneName::SunnyScene);*/
				this->navigateTo(SceneName::SunnyScene);
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
	wTurtle = new WTurtle(0, 0, 0, 0, 0, 0);
	
	ScoreBoard::getInstance()->resetTimeToZero();
	Camera::getInstance()->loadWorldMap();

	this->adaptData();
	this->adaptAnimation();
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

	if (wTurtle != NULL) {
		wTurtle->Update(_dt);
	}

	if (wMario != NULL) {
		wMario->Update(_dt);
	}
}

void WorldVC::viewWillRender()
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

		ScoreBoard::getInstance()->Draw();

		if (wTurtle != NULL) {
			wTurtle->Draw(map->getTexture());
		}

		if (wMario != NULL) {
			wMario->Draw(map->getTexture());
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void WorldVC::viewDidRender()
{
}

void WorldVC::adaptData()
{
	//Camera* camera = Camera::getInstance();
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

		//if (line == "<Camera>") {
		//	section = SECTION_CAMERA;
		//	continue;
		//}
		//else if (line == "</Camera>") {
		//	section = SECTION_NONE;
		//}
		if (line == "<MapInfo>") {
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
		else if (line == "<GrassFrames>") {
			section = SECTION_GRASS_FRAMES;
			continue;
		}
		else if (line == "</GrassFrames>") {
			grasses->loadFrames(data, ',');
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
		else if (line == "<WMarioMovingMatrix>") {
			section = SECTION_WMARIO_MOVING_MATRIX;
			continue;
		}
		else if (line == "</WMarioMovingMatrix>") {
			wMario->loadMovingMatrix(data, ' ');
			data.clear();
			section = SECTION_NONE;
		}
		else if (line == "<WTurtleInfo>") {
			section = SECTION_WTURTLE_INFO;
			continue;
		}
		else if (line == "</WTurtleInfo>") {
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
		//case SECTION_CAMERA:
		//	camera->load(line, ',');
		//	break;
		case SECTION_MAP_INFO:
			map->loadInfo(line, ',');
			break;
		case SECTION_MAP_INDEXES:
			data.push_back(line);
			break;
		case SECTION_GRASS_FRAMES:
			data.push_back(line);
			break;
		case SECTION_HELP_LABEL_FRAME:
			data.push_back(line);
			break;
		case SECTION_WMARIO_INFO:
			wMario->loadInfo(line, ',');
			break;
		case SECTION_WMARIO_MOVING_MATRIX:
			data.push_back(line);
			break;
		case SECTION_WTURTLE_INFO:
			wTurtle->loadInfo(line, ',');
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

void WorldVC::adaptAnimation()
{
	this->wMario->setAnimation(new Animation(AnimationBundle::getInstance()->getWMario()));
	this->grasses->setAnimation(new Animation(AnimationBundle::getInstance()->getGrasses()));
	this->helpLabel->setAnimation(new Animation(AnimationBundle::getInstance()->getHelpLabel()));
	this->wTurtle->setAnimation(new Animation(AnimationBundle::getInstance()->getWTurtle()));
}
