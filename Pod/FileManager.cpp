#include "FileManager.h"

FileManager* FileManager::instance;

FileManager* FileManager::getInstance()
{
	if (instance == nullptr) {
		instance = new FileManager();
	}
	return instance;
}

void FileManager::writeStringToTextFile(string fileName, string value)
{
	fstream f;
	f.open("./Assets/TextFiles/" + fileName, ios::out);
	f << value;
	f.close();
}

string FileManager::getStringFromTextFile(string fileName)
{
    fstream f;
    f.open("./Assets/TextFiles/" + fileName, ios::in);
    string data, line;

    while (!f.eof()) // eof: End Of File
    {
        getline(f, line);
        data += line;
    }

    f.close();

    return data;
}
