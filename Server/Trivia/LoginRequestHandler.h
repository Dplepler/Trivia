#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

typedef enum REQUEST_STATUS {

	FAILURE,
	SUCCESS

} REQUEST_STATUS;


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

