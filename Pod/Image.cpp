#include "Image.h"

Image::Image(int x, int y, LPCWSTR imagePath, D3DCOLOR _transcolor)
{
	this->texture = LoadTextureFromImage(imagePath, _transcolor);
	this->position = new D3DXVECTOR3(x, y, 0);
}

Image::~Image()
{
	delete this->position;
	delete& texture;
}

void Image::Update()
{
}

void Image::Draw()
{
	Drawing::getInstance()->draw(this->texture, NULL, NULL, this->position, D3DCOLOR_XRGB(255, 255, 255));
}

void Image::setColor(D3DCOLOR _color)
{
}
