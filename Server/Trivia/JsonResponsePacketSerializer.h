#pragma once
#include "json.hpp"
#include "IRequestHandler.h"
#include "Response.h"

#define BYTE 0xff
#define BYTE_BITS 0x8

#define SHIFT_MAX 24

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

