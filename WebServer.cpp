#define WIN32_LEAN_AND_MEAN
#include<iostream>
#include <stdio.h>
#include <windows.h>
#include<fstream>
#include<sstream>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
#include "FileHandling.h"
#include "HTML_Parser.h"

int main() {

	std::vector<StudentData> studentDataVec;
	WSADATA wsaData;
	int wsaError;
	WORD wVersionRequest = MAKEWORD(2, 2);
	wsaError = WSAStartup(wVersionRequest, &wsaData);

	if (wsaError != 0)
	{
		std::cout << "Error in finding winsock" << std::endl;
		return 0;
	}

	SOCKET serverSocket = INVALID_SOCKET;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "INVALID SOCKET " << std::endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in sockAddress;
	sockAddress.sin_addr.s_addr = INADDR_ANY;
	sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &sockAddress.sin_addr);
	sockAddress.sin_port = htons(8000);

	if (bind(serverSocket, (const sockaddr*)&sockAddress, sizeof(sockAddress)) < 0)
	{
		std::cout << "Binding error" << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	if (listen(serverSocket, 5) == SOCKET_ERROR)
	{
		std::cout << "Sunai nahi deta bhai" << std::endl;
	}
	SOCKET acceptSocket;
	char buffer[1024];
	while (1)
	{
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket < 0) {
			std::cout << "No accepted" << std::endl;
		}

		int received = recv(acceptSocket, buffer, sizeof(buffer), 0);
		if (received > 0)
		{
			//std::cout << buffer << std::endl;
			const char* sendbuf = "Client: sending data test";
			std::stringstream response;
			response << "HTTP/1.1 200 OK\r\n";
			response << "Content-Type: text/html\r\n\r\n";
			std::string temp;
			HTMLToString("index.html", temp);
			response << temp;
			std::string bufferstring(buffer);
			returnBody(studentDataVec, bufferstring);

			for (const auto& sd : studentDataVec)
			{
				std::cout << "Name = " << sd.name << std::endl;
				std::cout << "city = " << sd.city << std::endl;
				std::cout << "email = " << sd.email << std::endl;
			}

			int k = send(acceptSocket, response.str().c_str(), response.str().size(), 0);
			closesocket(acceptSocket);

		}
		
	}
	closesocket(serverSocket);
	return 0;
}