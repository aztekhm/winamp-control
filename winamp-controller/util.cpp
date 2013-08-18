#include "util.h"
#include <windows.h>

std::string utf8_encode(std::wstring source) {
    std::string title(WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), NULL, 0, NULL, NULL), 0);
    WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), &title[0], title.size(), NULL, NULL);
	return title;
}
