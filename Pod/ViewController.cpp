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
	this->background = new Component(new Rect(new Point(0, 0), Setting::getInstance()->getScreenSize()), Setting::getInstance()->getDefaultBackgroundColorViewController());
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
