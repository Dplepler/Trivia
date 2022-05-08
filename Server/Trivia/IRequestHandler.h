#pragma once
#include <vector>
#include <ctime>

typedef std::vector<unsigned char> Buffer;
typedef unsigned int RequestId;

typedef struct REQUEST_RESULT_STRUCT RequestResult;
typedef struct REQUEST_INFO_STRUCT  RequestInfo;



enum RequestCodes {

	SIGNUP_REQUEST_CODE = 11, 
	LOGIN_REQUEST_CODE,
	CREATE_ROOM_CODE,
	GET_ROOM_CODE,
	GET_ROOM_PLAYERS_CODE,
	JOIN_ROOM_CODE,
	GET_STATISTICS_CODE,
	LOGOUT_REQUEST_CODE
	
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
