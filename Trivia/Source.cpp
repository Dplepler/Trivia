#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"


int main() {

	WSAInitializer wsaInit;
	Server server = Server();
	server.run();

	return 0;
}