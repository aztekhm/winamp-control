#include "controller_threads.h"
#include <string>

DWORD WINAPI openWinampThread(LPVOID pathToWinamp) {
	std::string command("\"");
	command.append(((std::string*)pathToWinamp)->c_str());
	command.append("\"");
	system(command.c_str());
	return 0;
}
