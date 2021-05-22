#pragma once
#include <fstream>
#include "Tool.h"
#include "ImagePath.h"
#include "FilePath.h"

using namespace std;

// Singleton
class FileManager
{
private:
	FileManager() = default; // 1.Don't public constructor function
	static FileManager* instance; // 2. static private instance
	string rootFolderTextFile = "";

public:
	FileManager(const FileManager&) = delete; // 3. delete copy constructor
	static FileManager* getInstance();	  // 4. public function for client code usage

	void writeStringToTextFile(string fileName, string value);
	string getStringFromTextFile(string fileName);
	vector<vector<int>> getIntegerMatrixFromTextFile(string fileName, char seperator);


	// Animations
	vector<RECT*>* getFramesFrom(string fileName, char seperator);
};

