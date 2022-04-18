#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(IDatabase* db, RequestHandlerFactory* factory) {
	this->m_handlerFactory = factory;
	m_loginManager = m_handlerFactory->getLoginManager();
}

// checks that the request code is LoginRequestCode or SignupRequestCode, aka the request is revelevant to this handler
bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const { 
	return (reqInfo.id == LoginRequestCode || reqInfo.id == SignupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo) { 
	
	RequestResult result;
	
	result.newHandler = nullptr;


	if (reqInfo.id == SignupRequestCode) {
		result = signup(reqInfo);
	}
	else {
		result = login(reqInfo);
	}

	return result;
}



RequestResult LoginRequestHandler::login(RequestInfo reqInfo) { 
	LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
	SignupResponse res{ FAILURE };
	IRequestHandler* newHandler = nullptr;
	if (m_loginManager->login(loginReq.username, loginReq.password)) {
		res.status = SUCCESS;
		// should be changed in the future to menu handler or the matching handler 
		newHandler = m_handlerFactory->createLoginRequestHandler();
	}
	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(res), newHandler };
}


RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) { 
	SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
	LoginResponse res{ FAILURE };
	IRequestHandler* newHandler = nullptr;
	if (m_loginManager->signup(signupReq.username, signupReq.password, signupReq.email)) {
		res.status = SUCCESS;
		// should be changed in the future to menu handler or the matching handler 
		newHandler = m_handlerFactory->createLoginRequestHandler();
	}
	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(res), newHandler };
}