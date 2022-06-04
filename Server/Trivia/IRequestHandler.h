#pragma once
#include <vector>
#include <ctime>

typedef std::vector<unsigned char> Buffer;
typedef unsigned int RequestId;

typedef struct REQUEST_RESULT_STRUCT RequestResult;
typedef struct REQUEST_INFO_STRUCT  RequestInfo;



enum RequestCodes {

	SIGNUP_REQUEST_CODE = 11, 
	LOGIN_REQUEST_CODE = 12,
	CREATE_ROOM_CODE = 13,
	GET_ROOM_CODE = 14,
	GET_ROOM_STATE_CODE = 15,
	JOIN_ROOM_CODE = 16,
	GET_STATISTICS_CODE = 17,
	GET_HIGH_SCORE_CODE = 18, 
	LOGOUT_REQUEST_CODE = 19,
	START_GAME_CODE = 40,
	CLOSE_ROOM_CODE = 41,
	LEAVE_ROOM_CODE = 42
};



class IRequestHandler
{

public:

	IRequestHandler() = default;
	~IRequestHandler() = default;

	virtual bool isRequestRelevant(RequestInfo reqInfo) const = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;


};


// result and info structs, used for info to give to handlers and results to return from handlers

struct REQUEST_RESULT_STRUCT {

	Buffer response;
	IRequestHandler* newHandler;

};

struct REQUEST_INFO_STRUCT {

	RequestId id;
	time_t time;
	Buffer buffer;

};
