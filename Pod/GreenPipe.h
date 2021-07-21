#pragma once
#include "Component.h"
class GreenPipe : public Component
{
private:
	Animation* animation;
	int floorNumber;
	bool isBlackMode = false, isDownMode = false;

public:
	// Init
	GreenPipe(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);
	GreenPipe(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY, int _id = 0);

	// Getter
	bool getIsBlackMode();
	bool getIsDownMode();
	int getFloorNumber();

	// Setter
	//void setupAnimation();
	void setIsBlackMode(bool _isBlackMode);
	void setIsDownMode(bool _isDownMode);
	void setAnimation(Animation* _animation);

	void loadInfo(string line, char seperator);
	void Draw(LPDIRECT3DTEXTURE9 _texture);
};

