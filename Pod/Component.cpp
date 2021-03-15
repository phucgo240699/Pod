#include "Component.h"

Component::Component(RECT* _bounds, Color* _color)
{
	// General
	this->bounds = _bounds;

	// Surface
	this->color = _color;
	this->d3dColor = this->color->toD3DColor();
	surface = LoadBlankSurface(this->bounds->right, this->bounds->bottom);

	// Texture
	texture = NULL;
}

Component::Component(int x, int y, int width, int height, Color* _color)
{
	// General
	this->bounds = new RECT();
	this->bounds->top = y;
	this->bounds->bottom = y + height;
	this->bounds->left = x;
	this->bounds->right = x + width;

	// Surface
	this->color = _color;
	this->d3dColor = this->color->toD3DColor();
	surface = LoadBlankSurface(this->bounds->right - this->bounds->left, this->bounds->bottom - this->bounds->top);

	// Texture
	texture = NULL;
}

Component::Component(int x, int y, LPCWSTR imagePath, Color* _transparentColor)
{
	// General
	this->bounds = new RECT();
	this->bounds->left = x;
	this->bounds->top = y;

	// Surface
	surface = NULL;

	// Texture
	texture = LoadTextureFromImage(imagePath, _transparentColor->toD3DColor());
	this->transparentColor = _transparentColor;
	this->d3dTransparentColor = this->transparentColor->toD3DColor();
}

Component::~Component()
{
	delete bounds;
	delete color;
	delete& surface;
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
	this->d3dColor = this->color->toD3DColor();
}

void Component::Update()
{

}

void Component::Draw()
{
	if (texture != NULL) {
		Drawing::getInstance()->draw(texture, NULL, NULL, new D3DXVECTOR3(this->bounds->left, this->bounds->top, 0), D3DCOLOR_XRGB(255,255,255));
	}
	else {
		Drawing::getInstance()->draw(surface, this->bounds, this->d3dColor);
	}
}

void Component::jumpTo(int x, int y)
{
	int width = this->bounds->right - this->bounds->left, height = this->bounds->bottom - this->bounds->top;
	this->bounds->top = y;
	this->bounds->bottom = y + height;
	this->bounds->left = x;
	this->bounds->right = x + width;
}
