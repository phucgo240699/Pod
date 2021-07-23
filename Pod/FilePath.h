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

	// Mario
	string mario = "./Assets/TextFiles/mario.txt";

	// Map
	string sunny_map = "./Assets/TextFiles/sunny_map.txt";
	string world_map = "./Assets/TextFiles/world_map.txt";
	string underground_map = "./Assets/TextFiles/underground_map.txt";
	string third_map = "./Assets/TextFiles/third_map.txt";
	string cloudy_map = "./Assets/TextFiles/cloudy_map.txt";

	// Scoreboard
	string score_board = "./Assets/TextFiles/score_board.txt";

	// Setting
	string settings = "./Assets/TextFiles/settings.txt";

	// Camera
	string camer_world_map = "./Assets/TextFiles/camera_world_map.txt";
	string camera_sunny_map = "./Assets/TextFiles/camera_sunny_map.txt";
	string camera_underground_map = "./Assets/TextFiles/camera_underground_map.txt";
	string camera_third_map = "./Assets/TextFiles/camera_third_map.txt";
	string camera_cloudy_map = "./Assets/TextFiles/camera_cloudy_map.txt";

	// Grid
	string original_grid_sunny_map = "./Assets/TextFiles/original_grid_sunny_map.txt";
	string original_grid_underground_map = "./Assets/TextFiles/original_grid_underground_map.txt";
	string original_grid_third_map = "./Assets/TextFiles/original_grid_third_map.txt";
	string original_grid_cloudy_map = "./Assets/TextFiles/original_grid_cloudy_map.txt";

	string current_grid_sunny_map = "./Assets/TextFiles/current_grid_sunny_map.txt";
	string current_grid_third_map = "./Assets/TextFiles/current_grid_third_map.txt";

	// Animation Bundle
	string animation_bundle = "./Assets/TextFiles/animation_bundle.txt";
};
