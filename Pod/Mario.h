#pragma once
#include "Component.h"
#include "MarioState.h"

class Mario : public Component
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;
	int groundY = 500;
	int vX = 0;
	int vY = 0;
public:
	// Init
	Mario(int _x, int _y, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
	Mario(D3DXVECTOR3* _position, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);

	// De Init
	~Mario();

	// Getter
	MarioState getState();

	// Setter
	void setState(MarioState _state);

	// Inherit
	void Update();
	void Draw();
};

