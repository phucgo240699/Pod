#include "Drawing.h"
#include "Camera.h"

Drawing* Drawing::instance = NULL;
Drawing* Drawing::getInstance()
{
	if (instance == nullptr) {
		instance = new Drawing();
	}
	return instance;
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->Draw(texture, &_srcRect, _center, &_position, _color);
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->Draw(texture, &_srcRect, NULL, &_position, _color);
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, bool _isFlip, D3DCOLOR _color)
{
	if (_isFlip) {
		D3DXVECTOR2 scalePoint;
		D3DXVECTOR2 translation = D3DXVECTOR2(0,0);
		D3DXMATRIX matrix;
		D3DXMATRIX oldMatrix;

		_position.x -= Camera::getInstance()->getX();
		_position.y -= Camera::getInstance()->getY();

		float width = _srcRect.right - _srcRect.left;
		float height = _srcRect.bottom - _srcRect.top;
		scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, NULL, 0, &translation);

		D3DXVECTOR3 pos = D3DXVECTOR3(round(_position.x), round(_position.y), 0);

		spriteHandler->GetTransform(&oldMatrix);
		spriteHandler->SetTransform(&matrix);
		spriteHandler->Draw(texture, &_srcRect, NULL, &pos, _color);
		spriteHandler->SetTransform(&oldMatrix);
	}
	else {
		_position.x -= Camera::getInstance()->getX();
		_position.y -= Camera::getInstance()->getY();

		_position.x = round(_position.x);
		_position.y = round(_position.y);

		spriteHandler->Draw(texture, &_srcRect, NULL, &_position, _color);
	}

}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->Draw(texture, NULL, NULL, &_position, _color);
}

void Drawing::drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{
	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect.right - _srcRect.left;
		float height = _srcRect.bottom - _srcRect.top;
		scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, &rotationCenter, 0, &_translation);
	}

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(texture, &_srcRect, _center, &_position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}

void Drawing::drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x);
	_position.y = round(_position.y);
	spriteHandler->Draw(texture, &_srcRect, _center, &_position, _color);
}

void Drawing::drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x);
	_position.y = round(_position.y);
	spriteHandler->Draw(texture, &_srcRect, NULL, &_position, _color);
}

void Drawing::drawWithoutCamera(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x);
	_position.y = round(_position.y);
	spriteHandler->Draw(texture, NULL, NULL, &_position, _color);
}

void Drawing::drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x);
	_position.y = round(_position.y);
	spriteHandler->Draw(this->debugTexture, &_srcRect, _center, &_position, _color);
}

void Drawing::drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
{
	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect.right - _srcRect.left;
		float height = _srcRect.bottom - _srcRect.top;
		scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, &rotationCenter, 0, &_translation);
	}

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(this->debugTexture, &_srcRect, _center, &_position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}
