#pragma once
#include "Component.h"

class Image : public Component
{
private:
	// Properties
	D3DXVECTOR3* position;

	LPDIRECT3DTEXTURE9 texture;
public:
	// Init
	Image(int x, int y, LPCWSTR imagePath, D3DCOLOR _transcolor);

	// De Init
	~Image();

	// Inherit
	void Update();
	void Draw();

	// Un use
	void setColor(D3DCOLOR _color);
};

