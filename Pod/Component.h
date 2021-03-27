#pragma once
#include "Color.h"
#include "Drawing.h"

class Component {
protected:
	D3DXVECTOR3* position;
public:	
	// Init
	Component(int _x, int _y);
	Component(D3DXVECTOR3* _position);

	// De Init
	~Component();

	// Getter
	D3DXVECTOR3* getPosition();
	int getX();
	int getY();

	// Settter
	void setPosition(D3DXVECTOR3* _position);
	void setX(int _x);
	void setY(int _y);

	void plusX(int _x);
	void plusY(int _y);

	virtual void Update();
	virtual void Draw();
};