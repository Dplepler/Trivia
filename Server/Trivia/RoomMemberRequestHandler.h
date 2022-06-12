#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "BaseRoomRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public BaseRoomRequestHandler {

public:

    RoomMemberRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room);
    bool isRequestRelevant(RequestInfo info) const override;
    RequestResult handleRequest(RequestInfo info) override;

private:

    LoggedUser m_user;
    RoomManager* m_roomManager;
    RequestHandlerFactory& m_factory;

    std::mutex MemberLock;

    RequestResult leaveRoom(RequestInfo info);
};