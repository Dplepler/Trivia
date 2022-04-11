#include "JsonRequestPacketDeserializer.h"


using json = nlohmann::json;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer clientMsg) {
	

	json j = json::parse(clientMsg);

	LoginRequest logReq{
		j["username"].get<std::string>(),
		j["password"].get<std::string>()
	};

	return logReq;
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer clientMsg) {

	json j = json::parse(clientMsg);

	SignupRequest signupReq { 
		j["username"].get<std::string>(),
		j["password"].get<std::string>(),
		j["mail"].get<std::string>()
	};

	return signupReq;
}
