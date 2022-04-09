#include "LoginRequestHandler.h"




bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo) const { 
	if (reqInfo.id == LoginRequestCode || reqInfo.id == SignupRequestCode) {
		return true;
	}
	return false;
}



RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo) { 
	// since login/signup logic and next handlers don't exist yet, temporary code for next missions to replace
	Buffer buf;
	buf.push_back(1);
	RequestResult result{buf, nullptr};
	return result;
}



RequestResult LoginRequestHandler::login(RequestInfo reqInfo) { return RequestResult(); }

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo) { return RequestResult(); }