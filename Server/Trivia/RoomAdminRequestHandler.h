#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"
#include "BaseRoomRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public BaseRoomRequestHandler {

public:

    RoomAdminRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room);
    bool isRequestRelevant(RequestInfo info) const override;
    RequestResult handleRequest(RequestInfo info) override;

private:

    LoggedUser m_user;
    RoomManager* m_roomManager;
    RequestHandlerFactory& m_factory;

    std::mutex adminLock;

    RequestResult closeRoom(RequestInfo info);
    RequestResult startGame(RequestInfo info);
};