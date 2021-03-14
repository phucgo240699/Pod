#include "ViewController.h"

Component* ViewController::getBackground()
{
	return this->background;
}

void ViewController::setBackground(Component* _background)
{
	this->background = _background;
}

void ViewController::viewDidLoad()
{
	RECT* r = new RECT();
	r->bottom = Setting::getInstance()->getScreenHeight();
	r->right = Setting::getInstance()->getScreenWidth();
	this->background = new Component(r, Setting::getInstance()->getDefaultBackgroundColorViewController());
}

void ViewController::viewWillUpdate()
{
}

void ViewController::viewDidUpdate()
{
	background->update();
	for (int i = 0; i < this->components.size(); ++i) {
		components[i]->update();
	}
}

void ViewController::viewWillRender()
{
}

void ViewController::viewDidRender()
{
	background->draw();
	for (int i = 0; i < this->components.size(); ++i) {
		components[i]->draw();
	}
}

void ViewController::viewWillRelease()
{
}

void ViewController::addComponent(Component* _component)
{
	this->components.push_back(_component);
}
