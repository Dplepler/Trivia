#pragma once
#include <vector>
#include <ctime>

typedef std::vector<char> Buffer;
typedef unsigned int RequestId;

typedef struct REQUEST_RESULT_STRUCT RequestResult;
typedef struct REQUEST_INFO_STRUCT  RequestInfo;



class IRequestHandler
{

public:

	IRequestHandler() = default;
	~IRequestHandler() = default;

	virtual bool isRequestRelevant(RequestInfo info) const = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;


};

struct REQUEST_RESULT_STRUCT {

	Buffer response;
	IRequestHandler* newHandler;

};

struct REQUEST_INFO_STRUCT {

	RequestId id;
	time_t time;
	Buffer buffer;

};