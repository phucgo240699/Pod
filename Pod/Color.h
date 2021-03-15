#pragma once
#include <d3d9.h>
#include <string>

enum EnumColor {
	red, orange, yellow, green, blue, pinkFF00FF, purple, black, gray, white
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