#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <d3d9.h>
#include <d3dx9.h>
#include "Color.h"
#include "MarioState.h"

using namespace std;

// Singleton
class Tool {
public:
	static LPCWSTR getLPCWSTRFromCharArray(const char* charArray) {
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	/*static LPCWSTR getLPCWSTRFromString(string& s)
	{
		vector<wchar_t> buf(MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, 0, 0));

		MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, &buf[0], buf.size());

		return wstring(&buf[0]).c_str();
	}

	static wstring widen(string& s) {
		vector<wchar_t> buf(MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, 0, 0));

		MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, &buf[0], buf.size());

		return wstring(&buf[0]);
	}*/

	static string getStringFrom(LPCWSTR wString)
	{
		wstring ws(wString);
		return string(ws.begin(), ws.end());
	}

	static vector<string> splitToVectorStringFrom(string s, char seperator) {
		vector<string> vector;
		istringstream stm(s);
		
		size_t fromIndex = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			if (s[i] == seperator) {
				vector.push_back(s.substr(fromIndex, i - fromIndex));
				fromIndex = i + 1;
			}
		}

		vector.push_back(s.substr(fromIndex, s.length() - fromIndex));

		return vector;
	}

	static vector<int> splitToVectorIntegerFrom(string s, char seperator) {
		vector<int> vector;
		istringstream stm(s);

		size_t fromIndex = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			if (s[i] == seperator) {
				vector.push_back(stoi(s.substr(fromIndex, i - fromIndex)));
				fromIndex = i + 1;
			}
		}
		string a = s.substr(fromIndex, s.length() - fromIndex);
		if (a != "") {
			vector.push_back(stoi(a));
		}

		return vector;
	}

	static vector<float> splitToVectorFloatFrom(string s, char seperator) {
		vector<float> vector;
		istringstream stm(s);

		size_t fromIndex = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			if (s[i] == seperator) {
				vector.push_back(stof(s.substr(fromIndex, i - fromIndex)));
				fromIndex = i + 1;
			}
		}
		string a = s.substr(fromIndex, s.length() - fromIndex);
		if (a != "") {
			vector.push_back(stof(a));
		}

		return vector;
	}

	static vector<char> splitToVectorCharFrom(string s, char seperator) {
		vector<char> vector;
		istringstream stm(s);

		for (size_t i = 0; i < s.length(); ++i) {
			if (s[i] == seperator) continue;
			vector.push_back(s[i]);
		}

		return vector;
	}

	static pair<int, int> splitToPairIntIntFrom(string s, char seperator) {
		pair<int, int> p;

		size_t fromIndex = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			if (s[i] == seperator) {
				p.first = stoi(s.substr(0, i));
				p.second = stoi(s.substr(i + 1, s.length() - i - 1));
			}
		}
		return p;
	}

	static vector<vector<int>> getMatrixFrom(vector<string> data, char seperator) {
		vector<vector<int>> result = vector<vector<int>>();

		for (size_t i = 0; i < data.size(); ++i) {
			result.push_back(splitToVectorIntegerFrom(data[i], seperator));
		}

		return result;
	}

	static vector<vector<char>> getCharMatrixFrom(vector<string> data, char seperator) {
		vector<vector<char>> result = vector<vector<char>>();

		for (size_t i = 0; i < data.size(); ++i) {
			result.push_back(splitToVectorCharFrom(data[i], seperator));
		}

		return result;
	}

	static RECT getRECT(string line, char seperator) {
		RECT r = RECT();
		vector<int> v = splitToVectorIntegerFrom(line, seperator);

		r.left = v[0];
		r.top = v[1];
		r.right = r.left + v[2];
		r.bottom = r.top + v[3];

		return r;
	}

	static vector<RECT>* getRECTs(vector<string> data, char seperator) {
		vector<RECT>* RECTs = new vector<RECT>();

		for (size_t i = 0; i < data.size(); ++i) {
			RECTs->push_back(getRECT(data[i], seperator));
		}

		return RECTs;
	}

	static D3DXVECTOR3 getPositionFrom(string data, char seperator) {
		vector<float> v = splitToVectorFloatFrom(data, seperator);
		D3DXVECTOR3 position = D3DXVECTOR3(v[0], v[1], 0);
		return position;
	}

	static vector<D3DXVECTOR3> getPositionsFrom(vector<string> data, char seperator) {
		vector<D3DXVECTOR3> positions = vector<D3DXVECTOR3>();

		for (size_t i = 0; i < data.size(); ++i) {
			positions.push_back(getPositionFrom(data[i], seperator));
		}

		return positions;
	}

	static string getStringNumberFrom(int number, int length) {
		string result;
		string strNumber = to_string(number);

		for (size_t i = 0; i < length - strNumber.size(); ++i) {
			result.append("0");
		}

		return result.append(strNumber);
	}

	static EnumColor getColorFromString(string str) {
		if (str == "pinkFF00FF") return pinkFF00FF;
		if (str == "black") return black;
		if (str == "blue9CFCF0") return blue9CFCF0;
		else return white;

	}
	static string getStringFromColor(EnumColor color) {
		switch (color)
		{
		case pinkFF00FF:
			return "pinkFF00FF";
		case black:
			return "black";
		case blue9CFCF0:
			return "blue9CFCF0";
		default:
			return "white";
		}
	}

	static MarioState getMarioStateFromString(string str) {
		if (str == "DROPPING") return MarioState::DROPPING;
		else if (str == "JUMPING") return MarioState::JUMPING;
		else if (str == "STANDING") return MarioState::STANDING;
		else if (str == "WALKING") return MarioState::WALKING;
		else if (str == "DIE") return MarioState::DIE;
		else if (str == "DIE_JUMPING") return MarioState::DIE_JUMPING;
		else if (str == "DIE_DROPPING") return MarioState::DIE_DROPPING;
		else return MarioState::WALKING;
	}
};