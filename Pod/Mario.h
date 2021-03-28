#pragma once
#include "Component.h"
#include "MarioState.h"
#include "Keyboard.h"

class Mario : public Component
{
private:
	LPDIRECT3DTEXTURE9 texture;
	MarioState state;

	float vX = 0;
	float vY = 0;
public:
	// Init
	Mario(float _x, float _y, LPCWSTR _imagePath, D3DCOLOR _transcolor, MarioState _state);
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

	// Keyboard
	void onKeyUp();
	void onKeyDown(KeyType _keyType);
};

