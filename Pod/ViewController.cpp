#include "ViewController.h"

ViewController::ViewController()
{
	RECT* r = new RECT();
	r->bottom = Setting::getInstance()->getScreenHeight();
	r->right = Setting::getInstance()->getScreenWidth();
}

ViewController::~ViewController()
{
	for (int i = 0; i < components.size(); ++i) {
		delete components[i];
	}
	delete &components;
}

void ViewController::viewDidLoad()
{
}

void ViewController::viewReceiveKeyDown(KeyType _keyType)
{
}

void ViewController::viewReceiveKeyUp(KeyType _keyType)
{
}

void ViewController::viewWillUpdate()
{
}

void ViewController::viewDidUpdate()
{
	for (int i = 0; i < this->components.size(); ++i) {
		components[i]->Update();
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

		for (int i = 0; i < this->components.size(); ++i) {
			components[i]->Draw();
		}
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void ViewController::viewWillRelease()
{
}

void ViewController::addComponent(Component* _component)
{
	this->components.push_back(_component);
}
