#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{

public:

	LoginRequestHandler() = default;
	~LoginRequestHandler() = default;

	bool isRequestRelevant(RequestInfo reqInfo) const override;
	RequestResult handleRequest(RequestInfo info) override;


private:

	RequestResult login(RequestInfo reqInfo);
	RequestResult signup(RequestInfo reqInfo);


};

