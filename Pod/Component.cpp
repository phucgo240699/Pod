#include "Component.h"

Component::Component(Rect* _bounds, Color* _color)
{
	this->bounds = _bounds;
	this->color = _color;
}

Component::~Component()
{
	delete bounds;
}

Rect* Component::getBounds()
{
	return this->bounds;
}

void Component::setBounds(Rect* _bounds)
{
	this->bounds = _bounds;
}

Color* Component::getColor()
{
	return this->color;
}

void Component::setColor(Color* _color)
{
	this->color = _color;
}

void Component::update()
{

}

void Component::draw()
{
	Drawing::getInstance()->draw(this->bounds->getSize(), new Rect(new Point(10, 10), new Size(50, 50)), new D3DXVECTOR3(0,0,0), new D3DXVECTOR3(0, 0, 0), this->color);
}
