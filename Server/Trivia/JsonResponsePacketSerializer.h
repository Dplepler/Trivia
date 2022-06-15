#pragma once
#include "json.hpp"
#include "IRequestHandler.h"
#include "Response.h"
#include "Helper.h"


/*
Helper class to serialize all types of responses
*/
class JsonResponsePacketSerializer
{

public:

	static Buffer serializeResponse(ErrorResponse errorRes);
	static Buffer serializeResponse(LoginResponse loginRes);
	static Buffer serializeResponse(SignupResponse signupRes);
	static Buffer serializeResponse(LogoutResponse logoutRes);
	static Buffer serializeResponse(GetRoomsResponse getRoomsRes);
	static Buffer serializeResponse(JoinRoomResponse joinRoomRes);
	static Buffer serializeResponse(CreateRoomResponse createRoomRes);
	static Buffer serializeResponse(GetPersonalStatsResponse statsResponse);
	static Buffer serializeResponse(GetHighScoreResponse highScoreRes);
	static Buffer serializeResponse(CloseRoomResponse closeRoomRes);
	static Buffer serializeResponse(StartGameResponse startGameRes);
	static Buffer serializeResponse(GetRoomStateResponse getRoomStateRes);
	static Buffer serializeResponse(LeaveRoomResponse leaveRoomRes);
	static Buffer serializeResponse(SubmitAnswerResponse submitAnswerRes);
	static Buffer serializeResponse(LeaveGameResponse leaveGameRes);
	static Buffer serializeResponse(GetGameResultsResponse gameResultsRes);
	static Buffer serializeResponse(GetQuestionResponse getQuestionRes);
	

private:

	static void parseLength(Buffer& buffer, unsigned int length);
	static std::vector<std::string> parseRoomNameVec(std::vector<RoomData> vec);
	static std::vector<int> parseRoomIdVec(std::vector<RoomData> vec);
	static std::string parseStringVec(std::vector<std::string> vec);
	static std::string parseGameResults(PlayerResults res);
	static std::vector<std::string> parseAnswers(std::map<unsigned int, std::string> ansMap);
	

};

