#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler {

public:

    RoomAdminRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room);
    bool isRequestRelevant(RequestInfo info) const;
    RequestResult handleRequest(RequestInfo info);

private:

    LoggedUser m_user;
    Room* m_room;
    RoomManager* m_roomManager;
    RequestHandlerFactory& m_factory;

    std::mutex adminLock;

    RequestResult closeRoom(RequestInfo info);
    RequestResult startGame(RequestInfo info);
    RequestResult getRoomState(RequestInfo info);
};