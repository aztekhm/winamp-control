#include "server_threads.h"
#include "WinampServer.h"
#include "WinampController.h"
#include <iostream>
#include <sstream>

SOCKET SERVER_SOCKET;
SOCKET CLIENT_SOCKET;
WSADATA WSA_DATA;
SOCKADDR_IN SERVER_ADDRESS;
HWND LISTENER_WINDOW;
int PORT;
bool CLIENT_CONNECTED = false;
WinampServer* winampServer;

DWORD WINAPI waitForCommandsThread(LPVOID param) {

	for (;;) {
		
		if (WSAStartup(MAKEWORD(2,2), &WSA_DATA) != 0) {
			sendDataMessage(SERVER_MSG, "Winsock initialization failed");
			WSACleanup();
			return EXIT_FAILURE;
		}
		
		SERVER_SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (SERVER_SOCKET == INVALID_SOCKET) {
			sendDataMessage(SERVER_MSG, "Socket creation failed");
			WSACleanup();
			return EXIT_FAILURE;
		}
		
		SERVER_ADDRESS.sin_family = AF_INET;
		SERVER_ADDRESS.sin_addr.s_addr = INADDR_ANY;
		SERVER_ADDRESS.sin_port = htons(PORT);
		
		if (bind(SERVER_SOCKET, (SOCKADDR*)(&SERVER_ADDRESS), sizeof(SERVER_ADDRESS)) == SOCKET_ERROR) {
			sendDataMessage(SERVER_MSG, "Unable to bind server socket");
			WSACleanup();
			return EXIT_FAILURE;
		}

		if (listen(SERVER_SOCKET, SOMAXCONN) == SOCKET_ERROR) {
			sendDataMessage(SERVER_MSG, "Unable listen for connections");
			return EXIT_FAILURE;
		}
		
		CLIENT_SOCKET = SOCKET_ERROR;
		while (CLIENT_SOCKET == SOCKET_ERROR) {
			sendDataMessage(SERVER_MSG, "Waiting for incoming connections...");
			CLIENT_SOCKET = accept(SERVER_SOCKET, NULL, NULL);
		}
		
		u_long iMode=1;
		ioctlsocket(SERVER_SOCKET, FIONBIO, &iMode);
		
		CLIENT_CONNECTED = true;
		sendDataMessage(SERVER_MSG, "Client connected");
		if (winampServer->getSynchronizedMode()) {
			if (CreateThread(NULL, 0, synchronizePlayerThread, NULL, 0, NULL) == NULL) {
				sendDataMessage(SERVER_MSG, "Cannot start synchronization");
			}
		}
		
		for (;;) {
			int recvBytes = 0, error = 0;
			char buffer[DATA_LENGTH];
			
			recvBytes = recv(CLIENT_SOCKET, buffer, DATA_LENGTH, 0);		
			error = WSAGetLastError();
			if ((error != WSAEWOULDBLOCK && error !=0) || recvBytes == 0) {
				sendDataMessage(SERVER_MSG, "Client disconnected [R]");
				//shutdown(CLIENT_SOCKET, SD_RECEIVE);
				shutdown(CLIENT_SOCKET, 0);
				break;
			} else {
				HANDLE _requestThread;
				if ((_requestThread = CreateThread(NULL, 0, executeCommandThread, buffer, 0, NULL)) == NULL) {
					sendDataMessage(SERVER_MSG, "Cannot process request");
				}
			}
		}
		if (SERVER_SOCKET)
			closesocket(SERVER_SOCKET);
		if (CLIENT_SOCKET)
			closesocket(CLIENT_SOCKET);
		WSACleanup();
		CLIENT_CONNECTED = false;
	}
}

DWORD WINAPI executeCommandThread(LPVOID pRequest) {
	char *cRequest = (char*)pRequest;
	int sentBytes = 0, error = 0;
	
	std::string response = winampServer->parseRequest(cRequest);
	if (!response.empty()) {
		//sentBytes = send(CLIENT_SOCKET, response.c_str(), response.size() + 1, 0);	//por el fin de cadena "\0"
		sendData(response);
		error = WSAGetLastError();
		if (error != WSAEWOULDBLOCK && error !=0) {
			sendDataMessage(SERVER_MSG, "Client disconnected [S]");
			//shutdown(CLIENT_SOCKET, SD_SEND);
			shutdown(CLIENT_SOCKET, 1);
			closesocket(CLIENT_SOCKET);
		}
	}
	return 0;
}

DWORD WINAPI synchronizePlayerThread(LPVOID none) {
	WinampController winampController;
	while (CLIENT_CONNECTED && winampController.isWinampRunning()) {
		std::stringstream mainEqStream;
		mainEqStream << "syncmaineq_"
			<< winampController.getCurrentTrackInfo(TRACK_LENGTH) << "|"		//0
			<< winampController.getCurrentTrackInfo(PLAYBACK_POSITION) << "|"	//1
			<< winampController.getVolume() << "|"								//2
			<< winampController.getElementEqualizer(0) << "|"		//3
			<< winampController.getElementEqualizer(1) << "|"		//4
			<< winampController.getElementEqualizer(2) << "|"		//5
			<< winampController.getElementEqualizer(3) << "|"		//6
			<< winampController.getElementEqualizer(4) << "|"		//7
			<< winampController.getElementEqualizer(5) << "|"		//8
			<< winampController.getElementEqualizer(6) << "|"		//9
			<< winampController.getElementEqualizer(7) << "|"		//10
			<< winampController.getElementEqualizer(8) << "|"		//11
			<< winampController.getElementEqualizer(9) << "|"		//12
			<< winampController.getElementEqualizer(10) << "|"		//13
			<< winampController.getCurrentAudioInfo(AUDIO_SAMPLERATE) << "|"	//14
			<< winampController.getCurrentAudioInfo(AUDIO_BITRATE) << "|"		//15
			<< winampController.getCurrentAudioInfo(AUDIO_CHANNELS) << "|"		//16
			<< winampController.getMetadata("artist") << "|"	//17
			<< winampController.getMetadata("title") << "|"	//18
			<< (winampController.isRepeatOptionSet() ? "1" : "0") << "|"	//19
			<< (winampController.isShuffleOptionSet() ? "1" : "0");			//20
		
		int sentBytes, error;
		std::string buffer(mainEqStream.str());
		
		//sentBytes = send(CLIENT_SOCKET, buffer.c_str(), buffer.size() + 1, 0);	//por el fin de cadena "\0"
		sendData(buffer);
		error = WSAGetLastError();
		if (error != WSAEWOULDBLOCK && error !=0) {
			sendDataMessage(SERVER_MSG, "Cannot synchronize player");
			//shutdown(CLIENT_SOCKET, SD_SEND);
			shutdown(CLIENT_SOCKET, 1);
			closesocket(CLIENT_SOCKET);
		}
		
		int tracks = winampController.getTracksInPlaylist();
		
		std::stringstream playlistStream;
		playlistStream << "syncplaylist_" << winampController.getCurrentTrackInPlaylist();
		for (int i=0; i<tracks; i++) {
			playlistStream << "||" << winampController.getMetadata("artist", i) << "|" << winampController.getMetadata("title", i);
		}
		sendData(playlistStream.str());
		
		
		Sleep(1000);
	}
	return 0;
}

void sendDataMessage(int code, std::string message) {
	HWND _listenerWindow = LISTENER_WINDOW;
	if (_listenerWindow == NULL)
		return;
	
	COPYDATASTRUCT _dataStruct;
	_dataStruct.dwData = code;
	_dataStruct.lpData = (char*)message.c_str();
	_dataStruct.cbData = message.size() + 1;
	SendMessage(_listenerWindow, WM_COPYDATA, (WPARAM)_listenerWindow, (LPARAM)(LPVOID) &_dataStruct);
	
	std::cout << "Data Message[code:" << code << ", message:" << message << "]" << std::endl;
}

bool sendData(std::string data) {
	data.append("\n");
	return send(CLIENT_SOCKET, data.c_str(), data.size(), 0) != SOCKET_ERROR;
}
