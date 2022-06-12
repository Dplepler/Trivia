#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room)
    : m_user(user), m_factory(factory), BaseRoomRequestHandler(room) {

    this->m_roomManager = roomManager;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info) const {

    return info.id == LEAVE_ROOM_CODE ||
        info.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info) {

    switch (info.id) {

    case LEAVE_ROOM_CODE:     return leaveRoom(info);
    case GET_ROOM_STATE_CODE: return getRoomState(info);

    }
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info) {

    try {
        std::unique_lock<std::mutex> lock(this->MemberLock);
        m_room->removeUser(this->m_user);
        lock.unlock();
        return { JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse
                { REQUEST_STATUS::SUCCESS }), this->m_factory.createMenuRequestHandler(this->m_user) };
    }
    catch (...) {
        return { JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse
               { REQUEST_STATUS::FAILURE }), nullptr };
    }
}


