#include "View.h"

View::View(RECT* rect, D3DCOLOR _color)
{
	if (rect->left > rect->right || rect->top > rect->bottom) {
		throw "You've just passed an invalid rect";
	}
	this->bounds = rect;
	this->color = _color;

	surface = LoadBlankSurface(rect->right - rect->left, rect->bottom - rect->top);
}

View::View(int x, int y, int width, int height, D3DCOLOR _color)
{
	this->bounds = new RECT();
	this->bounds->top = y;
	this->bounds->bottom = y + height;
	this->bounds->left = x;
	this->bounds->right = x + width;
	this->color = _color;

	surface = LoadBlankSurface(width, height);
}

View::~View()
{
	delete bounds;
	delete& color;
	delete& surface;
}

void View::Update()
{
}

void View::Draw()
{
	Drawing::getInstance()->draw(surface, this->bounds, this->color);
}

void View::setColor(D3DCOLOR _color)
{
	this->color = _color;
}
