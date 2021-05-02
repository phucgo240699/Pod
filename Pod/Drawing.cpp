#include "Drawing.h"

Drawing* Drawing::instance = NULL;
Drawing* Drawing::getInstance()
{
	if (instance == nullptr) {
		return new Drawing();
	}
	return instance;
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color, bool _isFlip)
{
	if (_isFlip) {
		D3DXMATRIX matrix;
		D3DXMATRIX oldMatrix;
		float width = _srcRect->right - _srcRect->left;
		float height = _srcRect->bottom - _srcRect->top;

		D3DXMatrixTransformation2D(&matrix, new D3DXVECTOR2(_position->x + width / 2, _position->y + height / 2), 0, new D3DXVECTOR2(-1, 1), new D3DXVECTOR2(0, 0), 0, new D3DXVECTOR2(0, 0));

		spriteHandler->GetTransform(&oldMatrix);
		spriteHandler->SetTransform(&matrix);

		spriteHandler->Draw(texture, _srcRect, _center, _position, _color);

		spriteHandler->SetTransform(&oldMatrix);
	}
	else {
		spriteHandler->Draw(texture, _srcRect, _center, _position, _color);
	}
}

//void Drawing::draw(LPDIRECT3DSURFACE9 surface, RECT* _srcRect, D3DCOLOR _color)
//{
//	d3ddev->ColorFill(surface, NULL, _color);
//	d3ddev->StretchRect(surface, NULL, backbuffer, _srcRect, D3DTEXF_NONE);
//}
