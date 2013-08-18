#ifndef SERVER_THREADS_H
#define SERVER_THREADS_H

#include <windows.h>
#include <string>

#define DATA_LENGTH MAX_PATH
#define SERVER_MSG 777

DWORD WINAPI waitForCommandsThread(LPVOID pServer);
DWORD WINAPI executeCommandThread(LPVOID pRequest);
DWORD WINAPI synchronizePlayerThread(LPVOID none);

void sendDataMessage(int code, std::string message);
bool sendData(std::string data);


#endif
