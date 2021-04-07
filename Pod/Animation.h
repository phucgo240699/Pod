#pragma once
#include <vector>
#include <d3d9.h>

using namespace std;

class Animation
{
private:
	vector<RECT>* frames;

public:
	Animation(vector<RECT>* _frames);
};

