#include "StdAfx.h"
#include "util.h"
#include <windows.h>
#include <sstream>
#include <fstream>

std::string utf8_encode(std::wstring source) {
    std::string title(WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), NULL, 0, NULL, NULL), 0);
    WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), &title[0], title.size(), NULL, NULL);
	return title;
}


std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

std::string toStdString(int integer) {
	std::stringstream stringStream;
	stringStream << integer;
	return stringStream.str();
}

int toInteger(std::string string) {
	int integer;
	std::stringstream stringStream;
	stringStream << string;
	stringStream >> integer;
	return integer;
}
