// winamp-server-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WinampServer.h"
#include <iostream>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;
int main(int argc, char *argv[]) {
	system("cls");

	int port = 670;
	//cout << "Start on port: "; cin>> port;

	WSACleanup();
	WinampServer server(port);
	
	int mode = 0;
	stringstream argsStream;
	if (argc > 1) {
		argsStream << argv[1];
		argsStream >> mode;
	}
	
	cout << "mode:" << mode << endl;
	
	server.setSynchronizedMode(mode == 1 ? true : false);
	server.start();
	/*if (server.start() == false) {
		cout << "Server start failure. ";
		return 1;
	}*/
	
	cout << "Server listening at port " << port << endl;
	HANDLE _listenConnectionsThread = server.getServerThread();
	//HANDLE _receiveCommandsThread = server.getReceiveCommandsThread();
	//HANDLE _sendResponsesThread = server.getSendResponsesThread();
	/*for (int i=90; i>0; i--) {
		cout << "shutdown in " << i*10 << " seconds" << endl;
		Sleep(10000);
	}*/
	//server.stop();
	
	WaitForSingleObject(_listenConnectionsThread, INFINITE);
	//WaitForSingleObject(_receiveCommandsThread, INFINITE);
	//WaitForSingleObject(_sendResponsesThread, INFINITE);
	return 0;
}
