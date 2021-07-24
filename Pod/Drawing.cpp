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

LPDIRECT3DTEXTURE9 Drawing::getWorldMapTexture()
{
	return this->worldMapTexture;
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

LPDIRECT3DTEXTURE9 Drawing::getSunnyMapTexture()
{
	if (this->sunnyMapTexture == NULL) {
		this->sunnyMapTexture = LoadTextureFromImage(ImagePath::getInstance()->sunny_map, D3DCOLOR_XRGB(255, 0, 255));
	}
	return this->sunnyMapTexture;
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->Draw(texture, NULL, NULL, &_position, _color);
}

LPDIRECT3DTEXTURE9 Drawing::getUndergroundMapTexture()
{
	if (this->undergroundMapTexture == NULL) {
		this->undergroundMapTexture = LoadTextureFromImage(ImagePath::getInstance()->underground_map, D3DCOLOR_XRGB(255, 0, 255));
	}
	return this->undergroundMapTexture;
}

LPDIRECT3DTEXTURE9 Drawing::getThirdMapTexture()
{
	if (this->thirdMapTexture == NULL) {
		this->thirdMapTexture = LoadTextureFromImage(ImagePath::getInstance()->third_map, D3DCOLOR_XRGB(255, 0, 255));
	}
	return this->thirdMapTexture;
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

LPDIRECT3DTEXTURE9 Drawing::getCloudyMapTexture()
{
	if (this->cloudyMapTexture == NULL) {
		this->cloudyMapTexture = LoadTextureFromImage(ImagePath::getInstance()->cloudy_map, D3DCOLOR_XRGB(255, 0, 255));
	}
	return this->cloudyMapTexture;
}

void Drawing::drawMarioWithoutCamera(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, int _leftSpace, int _topSpace, int _rightSpace, bool _isFlip, D3DCOLOR _color)
{
	D3DXVECTOR2 scalePoint;
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	if (_isFlip) {
		float width = _srcRect.right - _srcRect.left;
		float height = _srcRect.bottom - _srcRect.top;
		scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
		_translation.x -= _rightSpace;
		_translation.y -= _topSpace;
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scaleReverse, &rotationCenter, 0, &_translation);
	}
	else {
		scalePoint = D3DXVECTOR2(0, 0);
		_translation.x -= _leftSpace;
		_translation.y -= _topSpace;
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

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DXVECTOR2 _translate, D3DCOLOR _color)
{
	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;

	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	float width = _srcRect.right - _srcRect.left;
	float height = _srcRect.bottom - _srcRect.top;
	D3DXVECTOR2 scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
	D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &scale, NULL, 0, &_translate);

	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(texture, &_srcRect, NULL, &_position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}

void Drawing::drawDebugBoxWithoutCamera(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x);
	_position.y = round(_position.y);
	spriteHandler->Draw(this->debugTexture, &_srcRect, _center, &_position, _color);
}

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, bool _isFlip, bool _isVerticalFlip, D3DCOLOR _color)
{

	if (_isFlip || _isVerticalFlip) {
		D3DXVECTOR2 scalePoint;
		D3DXVECTOR2 translation = D3DXVECTOR2(0, 0);
		D3DXMATRIX matrix;
		D3DXMATRIX oldMatrix;
		D3DXVECTOR2 tempScale = D3DXVECTOR2(_isFlip == true ? -1 : 1, _isVerticalFlip == true ? -1 : 1);

		_position.x -= Camera::getInstance()->getX();
		_position.y -= Camera::getInstance()->getY();

		float width = _srcRect.right - _srcRect.left;
		float height = _srcRect.bottom - _srcRect.top;
		scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
		D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &tempScale, NULL, 0, &translation);

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

void Drawing::draw(LPDIRECT3DTEXTURE9 texture, RECT _srcRect, D3DXVECTOR3 _position, D3DXVECTOR2 _translate, bool _isFlip, D3DCOLOR _color)
{

	D3DXMATRIX matrix;
	D3DXMATRIX oldMatrix;
	

	_position.x -= Camera::getInstance()->getX();
	_position.y -= Camera::getInstance()->getY();

	float width = _srcRect.right - _srcRect.left;
	float height = _srcRect.bottom - _srcRect.top;
	D3DXVECTOR2 scalePoint = D3DXVECTOR2(round(_position.x + width / 2), round(_position.y + height / 2));
	D3DXMatrixTransformation2D(&matrix, &scalePoint, 0, &(_isFlip == true ? scaleReverse : scale), NULL, 0, &_translate);

	/*D3DXVECTOR3 pos = D3DXVECTOR3(round(_position.x), round(_position.y), 0);*/
	_position.x = round(_position.x);
	_position.y = round(_position.y);

	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(texture, &_srcRect, NULL, &_position, _color);
	spriteHandler->SetTransform(&oldMatrix);
}

void Drawing::drawDebugBoxWithoutCamera(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DXVECTOR2 _translation, bool _isFlip, D3DCOLOR _color)
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

void Drawing::drawDebugBox(RECT _srcRect, D3DXVECTOR3* _center, D3DXVECTOR3 _position, D3DCOLOR _color)
{
	_position.x = round(_position.x - Camera::getInstance()->getX());
	_position.y = round(_position.y - Camera::getInstance()->getY());
	spriteHandler->Draw(this->debugTexture, &_srcRect, _center, &_position, _color);
}
