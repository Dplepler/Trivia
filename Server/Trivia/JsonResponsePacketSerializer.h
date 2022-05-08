#pragma once
#include "json.hpp"
#include "IRequestHandler.h"
#include "Response.h"
#include "Helper.h"


/*
Helper class to serialize all types of responses
*/
class JsonResponsePacketSerializer
{

public:

	static Buffer serializeResponse(ErrorResponse errorRes);
	static Buffer serializeResponse(LoginResponse loginRes);
	static Buffer serializeResponse(SignupResponse signupRes);
	/*static Buffer serializeResponse(LogoutResponse);
	static Buffer serializeResponse(SignupResponse signupRes);
	static Buffer serializeResponse(SignupResponse signupRes);
	static Buffer serializeResponse(SignupResponse signupRes);
	static Buffer serializeResponse(SignupResponse signupRes);
	static Buffer serializeResponse(SignupResponse signupRes);*/

private:

	static void parseLength(Buffer& buffer, unsigned int length);

};

