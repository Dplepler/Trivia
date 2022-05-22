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
	static Buffer serializeResponse(GetPlayersInRoomsResponse getPlayersRes);
	static Buffer serializeResponse(JoinRoomResponse joinRoomRes);
	static Buffer serializeResponse(CreateRoomResponse createRoomRes);
	static Buffer serializeResponse(GetPersonalStatsResponse statsResponse);
	static Buffer serializeResponse(GetHighScoreResponse highScoreRes);
	

private:

	static void parseLength(Buffer& buffer, unsigned int length);
	static std::string parseRoomNameVec(std::vector<RoomData> vec);
	static std::string parseRoomIdVec(std::vector<RoomData> vec);
	static std::string parseStringVec(std::vector<std::string> vec);

};

