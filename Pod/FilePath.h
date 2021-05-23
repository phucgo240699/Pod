#pragma once
#include <string>

using namespace std;

class FilePath {
private:
	FilePath() = default; // 1.Don't public constructor function
	static FilePath* instance; // 2. static private instance
public:
	FilePath(const FilePath&) = delete; // 3. delete copy constructor
	static FilePath* getInstance();	  // 4. public function for client code usage

	// Map
	string map_indexes_man1 = "./Assets/TextFiles/Map/Man1/indexes.txt";
	string map_info_man1 = "./Assets/TextFiles/Map/Man1/info.txt";
	string ground_man1 = "./Assets/TextFiles/Map/Man1/ground.txt";

	// Mario
	string mario_info = "./Assets/TextFiles/Mario/mario_info.txt";
	string mario_running = "./Assets/TextFiles/Mario/running.txt";
	string mario_standing = "./Assets/TextFiles/Mario/standing.txt";
	string mario_jumping_dropping = "./Assets/TextFiles/Mario/jumping_dropping.txt";

	// Camera
	string camera = "./Assets/TextFiles/Camera/camera.txt";

	// Setting
	string setting = "./Assets/TextFiles/Setting/setting.txt";
};
