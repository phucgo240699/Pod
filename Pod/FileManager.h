#pragma once
#include <string>
#include <fstream>

using namespace std;

// Singleton
class FileManager
{
private:
	FileManager() = default; // 1.Don't public constructor function
	static FileManager* instance; // 2. static private instance

public:
	FileManager(const FileManager&) = delete; // 3. delete copy constructor
	static FileManager* getInstance();	  // 4. public function for client code usage

	void writeStringToTextFile(string fileName, string value);
	string getStringFromTextFile(string fileName);
};

