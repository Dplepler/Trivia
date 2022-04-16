#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(IDatabase* db) {
	this->m_handlerFactory = new RequestHandlerFactory(db);
}

// checks that the request code is LoginRequestCode or SignupRequestCode, aka the request is revelevant to this handler
bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const { 
	return (reqInfo.id == LoginRequestCode || reqInfo.id == SignupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo) { 
	
	RequestResult result;
	SignupRequest signupReq;
	LoginRequest loginReq;
	
	result.newHandler = nullptr;


	if (reqInfo.id == SignupRequestCode) {

		signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
		result.response = JsonResponsePacketSerializer::serializeResponse(SignupResponse{ SUCCESS });
	}
	else {

		loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
		result.response = JsonResponsePacketSerializer::serializeResponse(LoginResponse{ SUCCESS });
	}

	return result;
}



RequestResult LoginRequestHandler::login(RequestInfo reqInfo) { return RequestResult(); }

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) { return RequestResult(); }