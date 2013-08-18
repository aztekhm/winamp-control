#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <map>

std::string utf8_encode(std::wstring source);
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);
std::string toStdString(int integer);
int toInteger(std::string string);

#endif