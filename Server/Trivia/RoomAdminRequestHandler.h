#pragma once
#include "LoggedUser.h"
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler {

public:

    RoomAdminRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room);
    bool isRequestRelevant(RequestInfo reqInfo) const;
    RequestResult handleRequest(RequestInfo reqInfo);

private:

    Room* m_room;

    RoomManager* m_roomManager;
  
    std::mutex adminLock;

    LoggedUser m_user;

    RequestHandlerFactory& m_factory;

    RequestResult closeRoom(RequestInfo info);
    RequestResult startGame(RequestInfo info);

    RequestResult getRoomState(RequestInfo info);
};