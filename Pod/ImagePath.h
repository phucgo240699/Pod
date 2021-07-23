#pragma once
#include <d3d9.h>


class ImagePath
{
private:
	ImagePath() = default; // 1.Don't public constructor function
	static ImagePath* instance; // 2. static private instance

public:
	ImagePath(const ImagePath&) = delete; // 3. delete copy constructor
	static ImagePath* getInstance();	  // 4. public function for client code usage

	LPCWSTR world_map = L"./Assets/Images/world_map.png";
	LPCWSTR sunny_map = L"./Assets/Images/sunny_map.png";
	LPCWSTR underground_map = L"./Assets/Images/underground_map.png";
	LPCWSTR third_map = L"./Assets/Images/third_map.png";
	LPCWSTR cloudy_map = L"./Assets/Images/cloudy_map.png";
	LPCWSTR mario = L"./Assets/Images/mario.png";
	LPCWSTR debug_box = L"./Assets/Images/debug_box.png";
	LPCWSTR board = L"./Assets/Images/board.png";

};

