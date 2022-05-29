#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H


#include "json.hpp"
#include "IRequestHandler.h"


#define MSG_HEADER_LEN 5



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


typedef struct GetPlayersInRoomRequest {

	unsigned int roomId;

} GetPlayersInRoomRequest;


typedef struct JoinRoomRequest {

	unsigned int roomId;

} JoinRoomRequest;

typedef struct CreateRoomRequest {

	std::string roomName;

	unsigned int maxUsers;

	unsigned int questionCount;

	unsigned int answerTimeout;


} CreateRoomRequest;




// deserializer itself

class JsonRequestPacketDeserializer {


public:

	
	static LoginRequest deserializeLoginRequest(Buffer clientMsg);

	static SignupRequest deserializeSignupRequest(Buffer clientMsg);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer clientMsg);

	static JoinRoomRequest deserializeJoinRoomRequest(Buffer clientMsg);

	static CreateRoomRequest deserializeCreateRoomRequest(Buffer clientMsg);


};









#endif // JSONDESERIALIZER_H
