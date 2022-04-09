#include "JsonRequestPacketDeserializer.h"


using json = nlohmann::json;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer jsonData) {
	
	json j = json::parse(jsonData);

	LoginRequest logReq{
		j["username"].get<std::string>(),
		j["password"].get<std::string>()
	};

	return logReq;
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer jsonData) {

	json j = json::parse(jsonData);

	SignupRequest signupReq { 
		j["username"].get<std::string>(),
		j["password"].get<std::string>(),
		j["mail"].get<std::string>()
	};

	return signupReq;
}
