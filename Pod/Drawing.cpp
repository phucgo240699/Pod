#include "Drawing.h"

Drawing* Drawing::instance = NULL;
Drawing* Drawing::getInstance()
{
	if (instance == nullptr) {
		return new Drawing();
	}
	return instance;
}

void Drawing::draw(Size* _size, Rect* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, Color* _color)
{
	LPDIRECT3DTEXTURE9 texture = LoadBlankTexture(_size);
	this->spriteHandler->Draw(texture, _srcRect->toPointerRECTForD3D(), _center, _position, _color->toD3DColor());
}

void Drawing::draw(char* _fileName, Size* _size, Rect* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, Color* _color)
{
	LPDIRECT3DTEXTURE9 texture = LoadTextureFromFile(_fileName, _color->toD3DColor());
	this->spriteHandler->Draw(texture, _srcRect->toPointerRECTForD3D(), _center, _position, _color->toD3DColor());
}
