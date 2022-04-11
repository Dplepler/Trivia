#include "JsonRequestPacketDeserializer.h"


using json = nlohmann::json;

/*
deserializeLoginRequest deserializes a login request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a login request struct
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer clientMsg) {
	

	json j = json::parse(clientMsg);

	LoginRequest logReq{
		j["username"].get<std::string>(),
		j["password"].get<std::string>()
	};

	return logReq;
}

/*
deserializeSignupRequest deserializes a signup request and returns it's structure
Input: Buffer to deserialize
Output: Deserialized buffer as a signup request struct
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer clientMsg) {

	json j = json::parse(clientMsg);

	SignupRequest signupReq { 
		j["username"].get<std::string>(),
		j["password"].get<std::string>(),
		j["mail"].get<std::string>()
	};

	return signupReq;
}
