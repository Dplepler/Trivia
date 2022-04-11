#pragma once
#include "json.hpp"
#include "IRequestHandler.h"
#include "Response.h"


/*
Helper class to serialize all types of responses
*/
class JsonResponsePacketSerializer
{

public:

	static Buffer serializeResponse(ErrorResponse errorRes);
	static Buffer serializeResponse(LoginResponse loginRes);
	static Buffer serializeResponse(SignupResponse signupRes);

private:

	static void parseLength(Buffer& buffer, unsigned int length);

};

