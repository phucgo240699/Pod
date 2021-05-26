#pragma once
#include <d3d9.h>
#include <string>

enum EnumColor {
	pinkFF00FF, black, white, blue9CFCF0,
};

class Color {
private:
	EnumColor value;

public:
	// Init
	Color(EnumColor _enumColor);

	// De Init
	~Color();

	// Getter
	EnumColor getValue();

	// Setter
	void setValue(EnumColor _enumColor);


	// Converter
	D3DCOLOR toD3DColor();
};