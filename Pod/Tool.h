#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <d3d9.h>
#include "Color.h"

using namespace std;

// Singleton
class Tool {
public:
	static LPCWSTR getLPCWSTRFromCharArray(const char* charArray) {
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	static LPCWSTR getLPCWSTRFromString(string& s)
	{
		vector<wchar_t> buf(MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, 0, 0));

		MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.size() + 1, &buf[0], buf.size());

		return wstring(&buf[0]).c_str();
	}

	static string getStringFrom(LPCWSTR wString)
	{
		wstring ws(wString);
		return string(ws.begin(), ws.end());
	}

	static vector<string> splitToVectorStringFrom(string s, char character) {
		vector<string> vector;
		istringstream stm(s);
		
		int fromIndex = 0;
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == character) {
				vector.push_back(s.substr(fromIndex, i - fromIndex));
				fromIndex = i + 1;
			}
		}

		vector.push_back(s.substr(fromIndex, s.length() - fromIndex));

		return vector;
	}

	static EnumColor getColorFromString(string str) {
		if (str == "red") return red;
		if (str == "orange") return orange;
		if (str == "yellow") return yellow;
		if (str == "green") return green;
		if (str == "blue") return blue;
		if (str == "pink") return pink;
		if (str == "purple") return purple;
		if (str == "black") return black;
		if (str == "gray") return gray;
		if (str == "white") return white;

	}
	static string getStringFromColor(EnumColor color) {
		switch (color)
		{
		case red:
			return "red";
		case orange:
			return "orange";
		case yellow:
			return "yellow";
		case green:
			return "green";
		case blue:
			return "blue";
		case pink:
			return "pink";
		case purple:
			return "purple";
		case black:
			return "black";
		case gray:
			return "gray";
		default:
			return "white";
		}
	}
};