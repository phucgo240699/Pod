#include "WorldVC.h"

void WorldVC::viewDidLoad()
{
	map = new WorldMap(ImagePath::getInstance()->world_map, D3DCOLOR_XRGB(255, 0, 255));
	this->adaptData();
}

void WorldVC::viewWillUpdate(float _dt)
{
	map->Update(_dt);
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
		default:
			break;
		}
	}

	fs.close();
}
