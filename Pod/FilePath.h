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

	// Scoreboard
	string score_board = "./Assets/TextFiles/score_board.txt";

	// Setting
	string settings = "./Assets/TextFiles/settings.txt";
};
