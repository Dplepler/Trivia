#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room room)
    : m_user(user), m_factory(factory), m_room(room) {

    this->m_roomManager = roomManager;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info) const {

    return info.id == CLOSE_ROOM_CODE ||
        info.id == START_GAME_CODE ||
        info.id == GET_ROOM_STATE_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info) {

    switch (info.id) {

    case CLOSE_ROOM_CODE: return closeRoom(info);
    case START_GAME_CODE: return startGame(info);
    case GET_ROOM_STATE_CODE: return getRoomState(info);

    }
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info) {
    
    try {
        
        this->m_room.setState(STATE::CLOSED);
        std::unique_lock<std::mutex> lock(this->adminLock);
        this->m_room.removeUser(this->m_user);
        lock.unlock();
        return { JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse
                { REQUEST_STATUS::SUCCESS }), this->m_factory.createMenuRequestHandler(this->m_user) };
    }
    catch (...) {
        std::cerr << "Error while closing room";
    }
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info) {
    try {
        this->m_room.setState(STATE::STARTED);
        return { JsonResponsePacketSerializer::serializeResponse(StartGameResponse
                { REQUEST_STATUS::SUCCESS }), nullptr };
    }
    catch (...) {
        std::cerr << "Error while starting game";
    }
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info) {

    try {
        RoomData data = this->m_room.getData();
        return { JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse
                { REQUEST_STATUS::SUCCESS, data.isActive, this->m_room.getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion }), nullptr };
    }
    catch (...) {
        std::cerr << "Error getting room state";
    }
}