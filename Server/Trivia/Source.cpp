#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"


int main() {


	try {
		

		WSAInitializer wsaInit;
		Server server;
		server.run();
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	

	return 0;
}
