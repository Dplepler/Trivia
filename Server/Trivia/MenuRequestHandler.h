#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {

public:

	MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager);
	bool isRequestRelevant(RequestInfo info) const;
	RequestResult handleRequest(RequestInfo info);

private:

	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory& m_factory;

	std::mutex menuLock;

	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
};