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

void ViewController::viewReceiveKeyDown(KeyType _keyType)
{
}

void ViewController::viewReceiveKeyUp()
{
}

void ViewController::viewWillUpdate()
{
}

void ViewController::viewDidUpdate()
{
	map->Update();
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

		map->Draw();

		spriteHandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void ViewController::viewWillRelease()
{
}
