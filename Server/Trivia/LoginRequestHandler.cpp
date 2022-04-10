#include "LoginRequestHandler.h"




// checks that the request code is LoginRequestCode or SignupRequestCode, aka the request is revelevant to this handler
bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const { 
	return (reqInfo.id == LoginRequestCode || reqInfo.id == SignupRequestCode);
}



RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo) { 
	// since login/signup logic and next handlers don't exist yet, temporary code for next missions to replace
	Buffer buf;
	buf.push_back((char)1);
	RequestResult result{buf, nullptr};
	return result;
}



RequestResult LoginRequestHandler::login(RequestInfo reqInfo) { return RequestResult(); }

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) { return RequestResult(); }