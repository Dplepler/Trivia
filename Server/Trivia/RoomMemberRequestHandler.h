#pragma once
#include "LoggedUser.h"
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;


class RoomMemberRequestHandler : public IRequestHandler {

public:

    RoomMemberRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room);
    bool isRequestRelevant(RequestInfo info) const override;
    RequestResult handleRequest(RequestInfo info) override;

private:

    RoomManager* m_roomManager;

    LoggedUser m_user;

    Room* m_room;

    RequestHandlerFactory& m_factory;

    std::mutex MemberLock;

    RequestResult getRoomState(RequestInfo info);

    RequestResult leaveRoom(RequestInfo info);
};