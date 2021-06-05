#include "Drawing.h"

Drawing* Drawing::instance = NULL;
Drawing* Drawing::getInstance()
{
	if (instance == nullptr) {
		instance = new Drawing();
	}
	return instance;
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{
	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect->right - _srcRect->left;
		float height = _srcRect->bottom - _srcRect->top;
		scalePoint = D3DXVECTOR2(_position->x + width / 2, _position->y + height / 2);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, &rotationCenter, 0, &_translation);
	}


	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(texture, _srcRect, _center, _position, _color);
	spriteHandler->SetTransform(&oldMatrix);
	//}
	/*else {
		spriteHandler->Draw(texture, _srcRect, _center, _position, _color);
	}*/
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color)
{
	spriteHandler->Draw(texture, _srcRect, _center, _position, _color);	
}

void Drawing::drawDebugBox(RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color)
{
	spriteHandler->Draw(this->debugTexture, _srcRect, _center, _position, _color);
}

void Drawing::drawDebugBox(RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{
	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect->right - _srcRect->left;
		float height = _srcRect->bottom - _srcRect->top;
		scalePoint = D3DXVECTOR2(_position->x + width / 2, _position->y + height / 2);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, &rotationCenter, 0, &_translation);
	}


	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(this->debugTexture, _srcRect, _center, _position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}

void Drawing::drawBoard(RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DCOLOR _color)
{
	spriteHandler->Draw(this->boardTexture, _srcRect, _center, _position, _color);
}

void Drawing::drawBoard(RECT* _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3* _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{

	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect->right - _srcRect->left;
		float height = _srcRect->bottom - _srcRect->top;
		scalePoint = D3DXVECTOR2(_position->x + width / 2, _position->y + height / 2);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, &rotationCenter, 0, &_translation);
	}


	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(this->boardTexture, _srcRect, _center, _position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}

//void Drawing::draw(LPDIRECT3DSURFACE9 surface, RECT* _srcRect, D3DCOLOR _color)
//{
//	d3ddev->ColorFill(surface, NULL, _color);
//	d3ddev->StretchRect(surface, NULL, backbuffer, _srcRect, D3DTEXF_NONE);
//}
