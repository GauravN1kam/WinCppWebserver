
#include<iostream>
#include <stdio.h>
#include <sys/socket.h>
#include<fstream>
#include <map>
#include<sstream>
#include <netinet/in.h>
#include <fcntl.h>
#include<unistd.h>
#include "FileHandling.h"
#include "routes.h"
#include "HTML_Parser.h"

int main() {

	std::vector<StudentData> studentDataVec;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		std::cout << "INVALID SOCKET " << std::endl;
		return 0;
	}

	sockaddr_in sockAddress;
	sockAddress.sin_addr.s_addr = INADDR_ANY;
	sockAddress.sin_family = AF_INET;
	sockAddress.sin_port = htons(8000);

	if (bind(serverSocket, (const sockaddr*)&sockAddress, sizeof(sockAddress)) < 0)
	{
		std::cout << "Binding error" << std::endl;
		close(serverSocket);
		return 0;
	}
	if (listen(serverSocket, 5) < 0)
	{
		std::cout << "Sunai nahi deta bhai" << std::endl;
	}

	std::map<std::string, std::string> Routes;

	addRoute(Routes, "/", "index.html");
	addRoute(Routes, "/about", "about.html");

	int acceptSocket;
	while (1)
	{
		char buffer[1024];
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket < 0) {
			std::cout << "No accepted" << std::endl;
		}

		int received = recv(acceptSocket, buffer, sizeof(buffer), 0);
		if (received > 0)
		{
			std::string line;
			std::stringstream method(buffer);
			std::getline(method, line);

			std::string method1 = "";
			std::string pathroute = "";
			std::string check;
			int counter = 0;
			std::stringstream line1(line);
			while(std::getline(line1, check, ' '))
			{
				if(counter == 0)
				{
					method1 = check;
				}
				else if(counter == 1)
				{
					pathroute = check;
				}
				else{
					break;
				}
				counter++;
			}

			if(method1 == "GET")
			{
				const char* sendbuf = "Client: sending data test";
				std::stringstream response;
				response << "HTTP/1.1 200 OK\r\n";
				response << "Content-Type: text/html\r\n\r\n";
				std::string temp;

				if(Routes.find(pathroute) != Routes.end())
				{
					HTMLToString(Routes[pathroute], temp);
				}
				else{
					temp = "<h1>Page Not Found</h1>";
				}
				response << temp;
				std::string bufferstring(buffer);
				returnBody(studentDataVec, bufferstring);


				int k = send(acceptSocket, response.str().c_str(), response.str().size(), 0);
				close(acceptSocket);
			}
			else if(method1 == "POST"){
				std::cout << "Its post method" << std::endl;
			}
		}
		
	}
	close(serverSocket);
	return 0;
}