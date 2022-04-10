#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H


#include "json.hpp"
#include "IRequestHandler.h"



// request structs for every request info to deserialize from json

typedef struct LoginRequest {

	std::string username;

	std::string password;


} LoginRequest;



typedef struct SignupRequest {

	std::string username;

	std::string password;

	std::string email;
} SignupRequest;



// deserializer itself

class JsonRequestPacketDeserializer {


public:

	
	static LoginRequest deserializeLoginRequest(Buffer clientMsg);

	static SignupRequest deserializeSignupRequest(Buffer clientMsg);


};









#endif // JSONDESERIALIZER_H
