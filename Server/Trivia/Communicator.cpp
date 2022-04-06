#include "Communicator.h"

/*
Constructor to start a server socket
*/
Communicator::Communicator() {

	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET) {
		throw std::exception(__FUNCTION__ " - socket");
	}
}

/*
Destructor to close all client connections and server listening socket
*/
Communicator::~Communicator() {

	try {

		/* Close client sockets */
		for (auto& it : this->m_clients) {
			delete it.second;
			closesocket(it.first);
		}

		/* Close server socket */
		closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests() {

	this->bindAndListen();		// Initialize server and start listening

	SOCKET clientSocket;

	std::thread server(&Communicator::serverHandler, this);	// Deal with tasks in a seperate thread
	server.detach();

	/* Insert each client to our map and handle them separately */
	for(;;) {
		
		std::cout << "Waiting for client connection request" << std::endl;
		
		clientSocket = this->acceptClient();

		/* Insert a client */
		std::unique_lock<std::mutex> lock(this->m_clientLock);
		this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, new LoginRequestHandler()));
		lock.unlock();

		/* Handle new client */
		std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
		clientThread.detach();		// Detach thread so it will run separately
	}
}

/*
bindAndListen initializes the server and starts pending for client connection
*/
void Communicator::bindAndListen() {

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(SERVER_PORT);	// port that server will listen for
	sa.sin_family = AF_INET;	// must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR) {
		std::cout << WSAGetLastError();
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << SERVER_PORT << std::endl;

}

/*
acceptClient accepts the client and creates a specific socket from the server to this client
The process will not continue until a client connects to the server

Output: Client socket
*/
SOCKET Communicator::acceptClient() {

	
	SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		throw std::exception(__FUNCTION__);
	}
	
	std::cout << "Client accepted. Server and client can speak" << std::endl;

	return client_socket;
}

/*
Handles server requests
*/
void Communicator::serverHandler() {
	
	/* Handle server requests, currently if EXIT is being requested we terminate the program */
	for (;;) {

		std::string data;
		std::cin >> data;

		if (data == "EXIT") { _exit(0); }
	}
}

/*
handleNewClient communicates with the client
Input: Client socket
*/
void Communicator::handleNewClient(SOCKET clientSock) {

	std::string clientMessage;

	try {

		for (;;) {

			Helper::sendData(clientSock, START_MESSAGE);

			clientMessage = Helper::getStringPartFromSocket(clientSock, strlen(START_MESSAGE));
			std::cout << clientMessage << std::endl;
		}
	}
	catch (...) { 

		std::unique_lock<std::mutex> lock(this->m_clientLock);
		this->m_clients.erase(clientSock);
		lock.unlock();
	}
	
}