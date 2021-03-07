#pragma once
#include <d3d9.h>
#include <string>

using namespace std;

enum EnumColor {
	red, orange, yellow, green, blue, pink, purple, black, gray, white
};

class Color {
private:
	EnumColor value;

public:
	// Init
	Color(EnumColor _enumColor);

	// Getter
	EnumColor getValue();

	// Setter
	void setValue(EnumColor _enumColor);


	// Converter
	D3DCOLOR toD3DColor();
};