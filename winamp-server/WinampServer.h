#pragma once
#ifndef WINAMPSERVER_H
#define WINAMPSERVER_H

#include <windows.h>
#include <string>
#include "server_threads.h"
#include "WinampController.h"

class WinampServer {
	protected:
		int _port;
		HWND _listenerWindow;
		HANDLE _serverThread;
		bool _synchronizedMode;
		WinampController* _winampController;
		
	public:
		static const int SERVER_STARTUP_SUCCESS = 667;
		static const int SERVER_STARTUP_ERROR = 668;
		static const int SERVER_SHUTDOWN = 669;
		static const int DEFAULT_PORT = 666;
		
		WinampServer();
		WinampServer(int port);
		~WinampServer();
		
		void setListenerWindow(HWND listenerWindow);
		HWND getListenerWindow();
		void setPort(int port);
		int getPort();
		HANDLE& getServerThread();
		void setWinampController(WinampController* winampController);
		WinampController* getWinampController();
		
		void start();
		void stop();
		std::string parseRequest(char *request);
		std::string executeCommand(int command, std::string param, std::string param2);
		void setSynchronizedMode(bool mode);
		bool getSynchronizedMode();
};

#endif
