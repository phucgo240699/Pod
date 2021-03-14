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
	//textureHandler = NULL;
	//textureHandler = LoadBlankTexture(_size);
	//spriteHandler->Draw(textureHandler, _srcRect->toPointerRECTForD3D(), _center, _position, _color->toD3DColor());
	if (d3ddev->BeginScene()) {
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		spriteHandler->Draw(texture, _srcRect, _center, _position, _color);
		spriteHandler->End();

		d3ddev->EndScene();
	}
	
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Drawing::draw(LPDIRECT3DSURFACE9 surface, RECT* _srcRect, D3DCOLOR _color)
{
	if (d3ddev->BeginScene()) {

		d3ddev->ColorFill(surface, NULL, _color);
		d3ddev->StretchRect(surface, NULL, backbuffer, _srcRect, D3DTEXF_NONE);

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}
