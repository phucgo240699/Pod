#include "ViewController.h"

ViewController::ViewController()
{
	RECT* r = new RECT();
	r->bottom = Setting::getInstance()->getScreenHeight();
	r->right = Setting::getInstance()->getScreenWidth();
	this->background = new View(r, Setting::getInstance()->getDefaultBackgroundColorViewController()->toD3DColor());
}

ViewController::~ViewController()
{
	delete background;
	for (int i = 0; i < components.size(); ++i) {
		delete components[i];
	}
	delete &components;
}

void ViewController::setBackgroundColor(D3DCOLOR _color)
{
	this->background->setColor(_color);
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
	background->Update();
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
		background->Draw();
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
