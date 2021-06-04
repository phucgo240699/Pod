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
	f.open(this->rootFolderTextFile + fileName, ios::out);
	f << value;
	f.close();
}

string FileManager::getStringFromTextFile(string fileName)
{
    fstream f;
    f.open(this->rootFolderTextFile + fileName, ios::in);

    string data, line;

    while (!f.eof()) // eof: End Of File
    {
        getline(f, line);
        if (line == "" || line[0] == '#') continue;
        data += line;
    }

    f.close();

    return data;
}

vector<vector<int>> FileManager::getIntegerMatrixFromTextFile(string fileName, char seperator)
{
    fstream f;
    f.open(this->rootFolderTextFile + fileName);

    vector<vector<int>> matrix;
    string line;

    while (!f.eof()) { // eof: End Of File
        getline(f, line);
        if (line == "" || line[0] == '#') continue;
        matrix.push_back(Tool::splitToVectorIntegerFrom(line, seperator));
    }

    f.close();
    return matrix;
}

vector<RECT*>* FileManager::getFramesFrom(string fileName, char seperator)
{
    fstream f;
    f.open(this->rootFolderTextFile + fileName);

    vector<RECT*>* frames = new vector<RECT*>();
    string line;
    vector<int> frame;
    RECT* r;

    while (!f.eof()) {
        getline(f, line);
        if (line == "" || line[0] == '#') continue;
        frame = Tool::splitToVectorIntegerFrom(line, seperator);
        r = new RECT();
        r->left = frame[0];
        r->top = frame[1];
        r->right = r->left + frame[2];
        r->bottom = r->top + frame[3];
        frames->push_back(r);
    }

    return frames;
}
