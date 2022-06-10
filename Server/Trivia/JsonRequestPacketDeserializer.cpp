#include "JsonRequestPacketDeserializer.h"


using json = nlohmann::json;


/*
deserializeLoginRequest deserializes a login request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a login request struct
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer clientMsg) {
	

	json j = json::parse(clientMsg);

	return LoginRequest {
		j["username"].get<std::string>(),
		j["password"].get<std::string>()
	};
}


/*
deserializeSignupRequest deserializes a signup request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a signup request struct
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer clientMsg) {

	json j = json::parse(clientMsg);

	return SignupRequest {
		j["username"].get<std::string>(),
		j["password"].get<std::string>(),
		j["mail"].get<std::string>()
	};
}



/*
deserializeGetPlayersRequest deserializes a get players in room request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a get players request struct
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(Buffer clientMsg) {

	json j = json::parse(clientMsg);

	return GetPlayersInRoomRequest {
		j["roomId"].get<unsigned int>()
	};
}


/*
deserializeJoinRoomRequest deserializes a join room request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a join room request struct
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer clientMsg) {
	
	json j = json::parse(clientMsg);

	return JoinRoomRequest {
		j["roomId"].get<unsigned int>()
	};
}


/*
deserializeCreateRoomRequest deserializes a create room request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a create room request struct
*/
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer clientMsg) {

	json j = json::parse(clientMsg);

	return CreateRoomRequest {
		j["roomName"].get<std::string>(),
		j["maxUsers"].get<unsigned int>(),
		j["questionCount"].get<unsigned int>(),
		j["answerTimeout"].get<unsigned int>()
	};

}


/*
deserializeSubmitAnswerRequest deserializes a submit answer request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a submit answer request struct
*/
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(Buffer clientMsg)
{
	json j = json::parse(clientMsg);

	return SubmitAnswerRequest{ j["answerId"].get<unsigned int>() };
}
