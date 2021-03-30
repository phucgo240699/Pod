#include "Drawing.h"

Drawing* Drawing::instance = NULL;
Drawing* Drawing::getInstance()
{
	if (instance == nullptr) {
		return new Drawing();
	}
	return instance;
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color)
{
	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spriteHandler->Draw(texture, _srcRect, _center, _position, _color);
	//spriteHandler->End();
}

void Drawing::draw(LPDIRECT3DSURFACE9 surface, RECT* _srcRect, D3DCOLOR _color)
{
	d3ddev->ColorFill(surface, NULL, _color);
	d3ddev->StretchRect(surface, NULL, backbuffer, _srcRect, D3DTEXF_NONE);
}
