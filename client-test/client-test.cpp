// cient-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")

void readLine(char *pBuffer, char *pLine);
int main(int argc, char *argv[])
{
	int port;
	system("cls");
	//std::cout << "Connect to port:"; std::cin >> port;

	//for (int i=0; i<256; i++) 
	{
		//Antes que nada
		WSADATA wsa;
		WSAStartup(MAKEWORD(2,0), &wsa);

		//1
		int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(sock == INVALID_SOCKET) {
			std::cout << "\nCannot create socket";
			return EXIT_FAILURE;
		}

		//2
		struct sockaddr_in direccion;
		direccion.sin_family = AF_INET;
		direccion.sin_port = htons(670);
		direccion.sin_addr.s_addr = inet_addr("127.0.0.1");

		//3
		if (connect(sock, (struct sockaddr*)&direccion, sizeof(direccion)) == INVALID_SOCKET){
			std::cout << "\n Cannot connect to server.";
			return EXIT_FAILURE;
		}

		for (;;) {
			//4
			char buffer[MAX_PATH];
			int error;
			
			std::cout << "\n\nCommand:"; gets(buffer);
			//std::cout << "\nbuufer to send:" << buffer;
			send(sock, buffer, MAX_PATH, 0);
			
			error = WSAGetLastError();
			if ((error != WSAEWOULDBLOCK && error !=0)) {
				std::cout << "\nDisconnected from Server";
				break;
			}

			char buffer2[MAX_PATH], line[MAX_PATH];
			int bytes = recv(sock, buffer2, MAX_PATH, 0);
			readLine(buffer2, line);
			
			error = WSAGetLastError();
			if ((error != WSAEWOULDBLOCK && error !=0) || bytes == 0) {
				std::cout << "\nDisconnected from Server";
				break;
			}
			
			std::cout << "Response:" << line;
		}
		closesocket(sock);
	}
	return EXIT_SUCCESS;
}
void readLine(char *pBuffer, char *pLine) {
	for (int i=0; i<MAX_PATH; i++) {
		if (pBuffer[i] == '\n') {
			pLine[i] = '\0';
			break;
		} else {
			pLine[i] = pBuffer[i];
		}
	}
}