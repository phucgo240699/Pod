#pragma once
#include "Color.h"
#include "KeyType.h"
#include "CollisionEdge.h"
#include "MarioState.h"
#include "Animation.h"
#include <tuple>
#include <vector>
#include <math.h>

using namespace std;

class Camera;

class Component {
protected:
	D3DXVECTOR3 position;
	float vx, vy;

	float limitX, limitY;
	float width, height;

	int id;

public:	
	// Init
	Component(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	Component(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	D3DXVECTOR3 getPosition();
	float getX();
	float getY();
	float getVx();
	float getVy();
	float getLimitX();
	float getLimitY();

	int getId();

	// Settter
	void setPosition(D3DXVECTOR3 _position);
	void setX(float _x);
	void setY(float _y);
	void setVx(float _vx);
	void setVy(float _vy);
	void setLimitX(float _limitX);
	void setLimitY(float _limitY);

	void setId(int _id);

	void plusX(float _x);
	void plusY(float _y);
	void plusXNoRound(float _x);
	void plusYNoRound(float _y);
	void plusVx(float _vx);
	void plusVy(float _vy);

	virtual void Update(float _dt);
	virtual void Draw();
	virtual void Draw(LPDIRECT3DTEXTURE9 _texture);
	virtual RECT getFrame();
	virtual RECT getBounds();
	virtual float getWidth();
	virtual float getHeight();
	virtual void setWidth(float _width);
	virtual void setHeight(float _height);

	// Keyboard
	virtual void onKeyUp();
	virtual void onKeyUp(vector<KeyType> _keyTypes);
	virtual void onKeyDown(vector<KeyType> _keyTypes);


	bool isColliding(RECT object, RECT other);


	// Collision by frame
	bool isCollidingByFrame(RECT other);
	RECT getSweptBroadphaseRectByFrame();
	tuple<bool, float, vector<CollisionEdge>> sweptAABBByFrame(Component* other, float _dt);

	// Collision by bounds
	bool isCollidingByBounds(RECT other);
	RECT getSweptBroadphaseRectByBounds();
	tuple<bool, float, vector<CollisionEdge>> sweptAABBByBounds(Component* other, float _dt);

};