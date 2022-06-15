#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

/*
Serialize a login response
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
Serialize a signup response
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
Serialize an error response
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

/*
Serialize a logout response
*/
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

/* Serialize a "get rooms" response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	/* Serialize the id's of the rooms and their names */

	buffer.push_back((char)RESPONSE::ROOMS);
	json["status"] = getRoomsRes.status;
	json["ids"] = parseRoomIdVec(getRoomsRes.rooms);
	json["names"] = parseRoomNameVec(getRoomsRes.rooms);

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a join rooms response */
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

/* Serialize a create room response */
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

/* Serialize a get statistics response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse statsResponse) {

	Buffer buffer;
	std::string jsonString;
	json json;

	/* Serialize the statistics vector as is */

	buffer.push_back((char)RESPONSE::STATS);
	json["status"] = statsResponse.status;
	json["statistics"] = statsResponse.statistics;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a high score response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse highScoreRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	/* Serialize the high score statistics vector */

	buffer.push_back((char)RESPONSE::HIGH_SCORE);
	json["status"] = highScoreRes.status;
	json["HighScores"] = highScoreRes.statistics;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a close room response */
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

/* Serialize a game start response */
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

/* Serialize a get room state response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	/* Serialize the room name, it's state (started, closed, open), the amount of players,
	 the amount of questions, answer timeout and max players */

	buffer.push_back((char)RESPONSE::STATE);
	json["status"] = getRoomStateRes.status;
	json["name"] = getRoomStateRes.name;
	json["state"] = getRoomStateRes.isActive;
	json["players"] = getRoomStateRes.players;
	json["questionCount"] = getRoomStateRes.questionCount;
	json["answerTimeout"] = getRoomStateRes.answerTimeout;
	json["maxPlayers"] = getRoomStateRes.maxPlayers;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a leave room response */
Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomRes) {
	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::LEAVE_ROOM);
	json["status"] = leaveRoomRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a submit answer response */
Buffer JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswerRes) {
	Buffer buffer;
	std::string jsonString;
	json json;

	/* Serialize the correct answer's Id */

	buffer.push_back((char)RESPONSE::SUBMIT);
	json["status"] = submitAnswerRes.status;
	json["correctAns"] = submitAnswerRes.correctAnswerId;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a leave game response */
Buffer JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leaveGameRes) {
	Buffer buffer;
	std::string jsonString;
	json json;

	buffer.push_back((char)RESPONSE::LEAVE_GAME);
	json["status"] = leaveGameRes.status;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a game results response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse gameResultsRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	std::vector<std::string> resJson;

	buffer.push_back((char)RESPONSE::RESULTS);
	json["status"] = gameResultsRes.status;

	/* Serialize the game results string vector */

	for (unsigned int i = 0; i < gameResultsRes.results.size(); i++) {
		resJson.push_back(JsonResponsePacketSerializer::parseGameResults(gameResultsRes.results[i]));
	}

	json["results"] = resJson;

	jsonString = json.dump();

	parseLength(buffer, jsonString.size());

	buffer.insert(buffer.end(), jsonString.begin(), jsonString.end());

	return buffer;
}

/* Serialize a get question response */
Buffer JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestionRes) {

	Buffer buffer;
	std::string jsonString;
	json json;

	std::vector<std::string> resJson;

	/* Serialize the question and it's possible answer */

	buffer.push_back((char)RESPONSE::GET_QUESTIONS);
	json["status"] = getQuestionRes.status;
	json["question"] = getQuestionRes.question;
	json["answers"] = parseAnswers(getQuestionRes.answers);

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

/* parseRoomNameVec parses a vector consisting of room data to a name string that is separated with commas */
std::vector<std::string> JsonResponsePacketSerializer::parseRoomNameVec(std::vector<RoomData> vec) {

	std::vector<std::string> names;

	if (vec.empty()) { return names; }
	
	for (auto& it : vec) { names.push_back(it.name); }
	
	return names;
}

/* parseRoomIdVec parses a vector consisting of room data to an id string that is separated with commas */
std::vector<int> JsonResponsePacketSerializer::parseRoomIdVec(std::vector<RoomData> vec) {

	std::vector<int> ids;

	if (vec.empty()) { return ids; }

	for (auto& it : vec) { ids.push_back(it.id); }

	return ids;
}

/* parseStringVec parses a vector containing strings into one string where the elements are separated with commas */
std::string JsonResponsePacketSerializer::parseStringVec(std::vector<std::string> vec) {

	if (vec.empty()) { return ""; }

	std::string result;
	for (auto& it : vec) {
		result += it;
		result += ", ";
	}

	return result.substr(0, result.size() - strlen(", "));
}

/* parses the game result struct into a json */
std::string JsonResponsePacketSerializer::parseGameResults(PlayerResults res) {

	json json;
	
	json["username"] = res.username;
	json["averageTime"] = res.averageAnswerTime;
	json["correctAns"] = res.correctAnswerCount;
	json["wrongAns"] = res.wrongAnswerCount;

	return json.dump();
}

/* parses an answer map into a string vector */
std::vector<std::string> JsonResponsePacketSerializer::parseAnswers(std::map<unsigned int, std::string> ansMap) {
	
	if (ansMap.empty()) { return std::vector<std::string> { " ", " ", " ", " " }; }

	std::vector<std::string> answers;
	
	answers.push_back(ansMap[1]);

	answers.push_back(ansMap[2]);

	answers.push_back(ansMap[3]);

	answers.push_back(ansMap[4]);

	return answers;
}


