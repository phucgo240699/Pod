#pragma once
#include "Color.h"
#include "Drawing.h"
#include "Keyboard.h"

class Component {
protected:
	D3DXVECTOR3* position;
public:	
	// Init
	Component(float _x, float _y);
	Component(D3DXVECTOR3* _position);

	// De Init
	~Component();

	// Getter
	D3DXVECTOR3* getPosition();
	float getX();
	float getY();

	// Settter
	void setPosition(D3DXVECTOR3* _position);
	void setX(float _x);
	void setY(float _y);

	void plusX(float _x);
	void plusY(float _y);

	virtual void Update();
	virtual void Draw();

	// Keyboard
	virtual void onKeyUp();
	virtual void onKeyDown(KeyType _keyType);
};