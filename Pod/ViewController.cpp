#include "ViewController.h"

ViewController::ViewController()
{
	Camera::getInstance()->load();
}

ViewController::~ViewController()
{
	delete& mainCharacter;
}

void ViewController::viewDidLoad()
{
	int a = 0;
}

void ViewController::viewReceiveKeyDown(vector<KeyType> _keyTypes)
{
	mainCharacter->onKeyDown(_keyTypes);
}

void ViewController::viewReceiveKeyUp()
{
	mainCharacter->onKeyUp();
}

void ViewController::viewReceiveKeyUp(vector<KeyType> _keyTypes)
{
	mainCharacter->onKeyUp(_keyTypes);
}

void ViewController::viewWillUpdate(float _dt)
{
}

void ViewController::viewDidUpdate(float _dt)
{
	if (map != NULL) {
		map->Update(_dt);
	}
	if (mainCharacter != NULL) {
		mainCharacter->Update(_dt);
		Camera::getInstance()->follow(mainCharacter, _dt);
	}
}

void ViewController::viewWillRender()
{
}

void ViewController::viewDidRender()
{
	if (d3ddev->BeginScene()) {
		// Clear backbuffer
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor(), 1.0f, 0);
		
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (map != NULL) {
			map->Draw();
		}
		if (mainCharacter != NULL) {
			mainCharacter->Draw();
		}

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void ViewController::viewWillRelease()
{
}
