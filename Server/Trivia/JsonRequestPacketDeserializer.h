#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H


#include "json.hpp"
#include "IRequestHandler.h"
#include <ctime>




typedef struct LoginRequest {

	std::string username;

	std::string password;


} LoginRequest;



typedef struct SignupRequest {

	std::string username;

	std::string password;

	std::string email;
};




class JsonRequestPacketDeserializer {


public:

	
	static LoginRequest deserializeLoginRequest(Buffer clientMsg);

	static SignupRequest deserializeSignupRequest(Buffer clientMsg);


};









#endif // JSONDESERIALIZER_H
