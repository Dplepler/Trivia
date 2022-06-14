#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"

#define ANSWERS_PER_QUESTION 4

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {

public:

	GameRequestHandler(LoggedUser user, Game* game, GameManager* manager, RequestHandlerFactory& factory);

	bool isRequestRelevant(RequestInfo info) const override;
	RequestResult handleRequest(RequestInfo info) override;

private:

	Game* m_game;
	LoggedUser m_user;
	GameManager* m_gameManager;
	RequestHandlerFactory& m_factory;

	std::mutex gameLock;

	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResult(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);

};