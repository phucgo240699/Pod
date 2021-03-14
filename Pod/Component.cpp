#include "Component.h"

Component::Component(RECT* _bounds, Color* _color)
{
	this->bounds = _bounds;
	this->color = _color;
	surface = LoadBlankSurface(this->bounds->right, this->bounds->bottom);
}

Component::~Component()
{
	delete bounds;
}

RECT* Component::getBounds()
{
	return this->bounds;
}

void Component::setBounds(RECT* _bounds)
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
	Drawing::getInstance()->draw(surface, this->bounds, this->color->toD3DColor());
}
