#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler : IRequestHandler {

public:

	MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager& room, StatisticsManager& statistics);
	bool isRequestRelevant(RequestInfo info) const;
	RequestResult handleRequest(RequestInfo info);

private:

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_factory;

	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
};