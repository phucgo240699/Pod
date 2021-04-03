#pragma once
#include "Color.h"
#include "Drawing.h"
#include "Keyboard.h"

class Component {
protected:
	D3DXVECTOR3* position;
	float vx, vy;
	float limitX, limitY;
public:	
	// Init
	Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY);
	Component(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY);

	// De Init
	~Component();

	// Getter
	D3DXVECTOR3* getPosition();
	float getX();
	float getY();
	float getVx();
	float getVy();
	float getLimitX();
	float getLimitY();

	// Settter
	void setPosition(D3DXVECTOR3* _position);
	void setX(float _x);
	void setY(float _y);
	void setVx(float _vx);
	void setVy(float _vy);
	void setLimitX(float _limitX);
	void setLimitY(float _limitY);

	void plusX(float _x);
	void plusY(float _y);

	virtual void Update(int _dt);
	virtual void Draw();
	virtual RECT* getBounds();

	// Keyboard
	virtual void onKeyUp();
	virtual void onKeyDown(KeyType _keyType);
};