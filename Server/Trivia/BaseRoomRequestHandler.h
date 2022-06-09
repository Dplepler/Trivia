#pragma once

#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


class BaseRoomRequestHandler : public IRequestHandler {
public:

    BaseRoomRequestHandler(Room* room); 
    BaseRoomRequestHandler() = default;

protected:

    RequestResult getRoomState(RequestInfo info);

    Room* m_room;

};
