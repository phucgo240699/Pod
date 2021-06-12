#pragma once
#include "Color.h"
#include "Drawing.h"
#include "KeyType.h"
#include "CollisionEdge.h"
#include "MarioState.h"
#include "Animation.h"
#include <tuple>
#include <vector>
#include <math.h>

using namespace std;

class Component {
protected:
	D3DXVECTOR3* position;
	float vx, vy;
	//float currentVx, currentVy;
	float limitX, limitY;
	float width, height;
	int id;
	int cellX, cellY;
public:	
	// Init
	Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0, int _cellX = 0, int _cellY = 0);
	Component(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0, int _cellX = 0, int _cellY = 0);

	// Getter
	D3DXVECTOR3* getPosition();
	float getX();
	float getY();
	float getVx();
	float getVy();
	float getLimitX();
	float getLimitY();
	int getId();
	int getCellX();
	int getCellY();

	// Settter
	void setPosition(D3DXVECTOR3* _position);
	void setX(float _x);
	void setY(float _y);
	void setVx(float _vx);
	void setVy(float _vy);
	void setLimitX(float _limitX);
	void setLimitY(float _limitY);
	void setId(int _id);
	void setCellX(int _cellX);
	void setCellY(int _cellY);

	void plusX(float _x);
	void plusY(float _y);
	void plusVx(float _vx);
	void plusVy(float _vy);

	virtual void Update(float _dt);
	virtual void Draw();
	virtual void Draw(LPDIRECT3DTEXTURE9 _texture);
	virtual RECT getBounds();
	virtual float getWidth();
	virtual float getHeight();
	virtual void setWidth(float _width);
	virtual void setHeight(float _height);

	// Keyboard
	virtual void onKeyUp();
	virtual void onKeyUp(vector<KeyType> _keyTypes);
	virtual void onKeyDown(vector<KeyType> _keyTypes);


	// Collision
	bool isColliding(RECT other);
	bool isColliding(RECT object, RECT other);
	RECT getSweptBroadphaseRect();
	tuple<bool, float, vector<CollisionEdge>> sweptAABB(Component* other, float _dt);

};