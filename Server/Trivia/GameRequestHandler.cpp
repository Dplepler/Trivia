#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo info) { 

	return info.id == LEAVE_GAME_CODE ||
			info.id == GET_QUESTION_CODE ||
			info.id == SUBMIT_ANSWER_CODE ||
			info.id == GAME_RES_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info) { 

	switch (info.id) {

	case LEAVE_GAME_CODE:		return leaveGame(info);
	case GET_QUESTION_CODE:		return getQuestion(info);
	case SUBMIT_ANSWER_CODE:	return submitAnswer(info);
	case GAME_RES_CODE:			return getGameResult(info);	

	}
}

	

RequestResult GameRequestHandler::getQuestion(RequestInfo info) { return RequestResult{}; }

RequestResult GameRequestHandler::submitAnswer(RequestInfo info) { return RequestResult{}; }

RequestResult GameRequestHandler::getGameResult(RequestInfo info) { return RequestResult{}; }

RequestResult GameRequestHandler::leaveGame(RequestInfo info) { return RequestResult{}; }