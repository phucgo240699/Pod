#pragma once
#include "Color.h"
#include "Drawing.h"
#include "Keyboard.h"

class Component {
protected:
	D3DXVECTOR3* position;
	float vx, vy, dt;
	float limitX, limitY;
public:	
	// Init
	Component(float _x, float _y, float _vx, float _vy, float _dt, float _limitX, float _limitY);
	Component(D3DXVECTOR3* _position, float _vx, float _vy, float _dt, float _limitX, float _limitY);

	// De Init
	~Component();

	// Getter
	D3DXVECTOR3* getPosition();
	float getX();
	float getY();
	float getVx();
	float getVy();
	float getDt();
	float getLimitX();
	float getLimitY();

	// Settter
	void setPosition(D3DXVECTOR3* _position);
	void setX(float _x);
	void setY(float _y);
	void setVx(float _vx);
	void setVy(float _vy);
	void setDt(float _dt);
	void setLimitX(float _limitX);
	void setLimitY(float _limitY);

	void plusX(float _x);
	void plusY(float _y);

	virtual void Update();
	virtual void Draw();
	virtual RECT* getBounds();

	// Keyboard
	virtual void onKeyUp();
	virtual void onKeyDown(KeyType _keyType);
};