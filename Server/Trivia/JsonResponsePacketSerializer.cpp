#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

/*
This instance of serializeResponse takes a login response and parses it into a buffer
Input: Login response
Output: Buffer containing response as a char vector
*/
Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes) {

	json json;
	std::string jsonString;
	Buffer buffer; 

	buffer.push_back((char)RESPONSE::LOGIN);
	json["status"] = loginRes.status;

	jsonString = json.dump();	// It is crucial to not dump directly, we should put the json into a string first

	parseLength(buffer, jsonString.size());		// Insert length to buffer

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());	// Insert json contents to buffer

	return buffer;
}

/*
This instance of serializeResponse takes a sign up response and parses it into a buffer
Input: Sign up response
Output: Buffer containing response as a char vector
*/
Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes) {

	json json;
	std::string jsonString;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::SIGNUP);
	json["status"] = signupRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/*
This instance of serializeResponse takes an error response and parses it into a buffer
Input: Error response
Output: Buffer containing response as a char vector
*/
Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes) {

	json json;
	std::string jsonString;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::ERROR_RES);
	json["message"] = errorRes.message;

	jsonString = json.dump();	

	parseLength(buffer, jsonString.size());		

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());	

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::LOGOUT);
	json["status"] = logoutRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::ROOMS);
	json["status"] = getRoomsRes.status;
	json["ids"] = parseRoomIdVec(getRoomsRes.rooms);
	json["names"] = parseRoomNameVec(getRoomsRes.rooms);

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::JOIN);
	json["status"] = joinRoomRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::CREATE);
	json["status"] = createRoomRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse statsResponse) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::STATS);
	json["status"] = statsResponse.status;
	json["statistics"] = statsResponse.statistics;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse highScoreRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::HIGH_SCORE);
	json["status"] = highScoreRes.status;
	json["HighScores"] = highScoreRes.statistics;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::CLOSE);
	json["status"] = closeRoomRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::START);
	json["status"] = startGameRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::STATE);
	json["status"] = getRoomStateRes.status;
	json["begun"] = getRoomStateRes.isActive;
	json["players"] = getRoomStateRes.players;
	json["questionCount"] = getRoomStateRes.questionCount;
	json["answerTimeout"] = getRoomStateRes.answerTimeout;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomRes) {
	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::LEAVE);
	json["status"] = leaveRoomRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}


/*
parseLength parses an integer value into a buffer, each digit becomes an index in the vector buffer
Input: Buffer, length to parse into buffer
*/
void JsonResponsePacketSerializer::parseLength(Buffer& buffer, unsigned int length) {

	for (int8_t i = MAX_SHIFT; i >= 0; i -= BYTE_BITS) {
		buffer.push_back(length >> i & BYTE);
	}
}

/*
parseRoomNameVec parses a vector consisting of room data to a name string that is separated with commas
*/
std::vector<std::string> JsonResponsePacketSerializer::parseRoomNameVec(std::vector<RoomData> vec) {

	std::vector<std::string> names;

	if (vec.empty()) { return names; }
		
	
	for (auto& it : vec) { names.push_back(it.name); }
	
	return names;
}

/*
parseRoomIdVec parses a vector consisting of room data to an id string that is separated with commas
*/
std::vector<int> JsonResponsePacketSerializer::parseRoomIdVec(std::vector<RoomData> vec) {

	std::vector<int> ids;

	if (vec.empty()) { return ids; }

	for (auto& it : vec) { ids.push_back(it.id); }

	return ids;
}

/*
parseStringVec parses a vector containing strings into one string where the elements are separated with commas
*/
std::string JsonResponsePacketSerializer::parseStringVec(std::vector<std::string> vec) {

	if (vec.empty()) { return ""; }

	std::string result;
	for (auto& it : vec) {
		result += it;
		result += ", ";
	}

	return result.substr(0, result.size() - strlen(", "));
}


