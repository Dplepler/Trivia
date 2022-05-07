#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"

class MenuRequestHandler {

public:

	bool isRequestRelevant(RequestInfo info) const;
	RequestResult handleRequest(RequestInfo info);

private:

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;


};