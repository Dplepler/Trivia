#include "LoginRequestHandler.h"

/* Constructor */
LoginRequestHandler::LoginRequestHandler(IDatabase* db, RequestHandlerFactory* factory) {
	this->m_handlerFactory = factory;
	m_loginManager = m_handlerFactory->getLoginManager();
}

/* Checks that the request code is LoginRequestCode or SignupRequestCode, aka the request is revelevant to this handler */
bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const { 
	return (reqInfo.id == LOGIN_REQUEST_CODE || reqInfo.id == SIGNUP_REQUEST_CODE);
}

/* Check for login and signup requests */
RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo) { 

	switch (reqInfo.id) {

		case SIGNUP_REQUEST_CODE:	return signup(reqInfo);
		case LOGIN_REQUEST_CODE:	return login(reqInfo);

	}

	return RequestResult {};	// Should never be reached but the compiler will still complain
}

/* Client request to log in to their account */
RequestResult LoginRequestHandler::login(RequestInfo reqInfo) { 
	LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
	LoginResponse res{ FAILURE };
	MenuRequestHandler* newHandler = nullptr;

	/* Try to log in, if succeeded we can create a new menu handler for the client to use */
	if (m_loginManager->login(loginReq.username, loginReq.password)) {
		res.status = SUCCESS;
		newHandler = this->m_handlerFactory->createMenuRequestHandler(m_loginManager->getUsers().back());
	}

	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)newHandler };
}

/* Client request to sign up to the game with a new user */
RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) { 
	SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
	SignupResponse res{ FAILURE };
	MenuRequestHandler* newHandler = nullptr;

	/* Try to sign up, if succeeded we can create a new menu handler for the client to use */
	if (m_loginManager->signup(signupReq.username, signupReq.password, signupReq.email)) {
		res.status = SUCCESS;
	
		newHandler = this->m_handlerFactory->createMenuRequestHandler(m_loginManager->getUsers().back());
	}

	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)newHandler };
}