#include "RoomAdminRequestHandler.h"

/* Constructor */
RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager, Room* room)
    : m_user(user), m_factory(factory), m_room(room) {

    this->m_roomManager = roomManager;
}

/* Check for a request that is relevant to a room admin (Only return true for things that the admin is allowed to do in the room) */
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info) const {

    return info.id == CLOSE_ROOM_CODE ||
        info.id == START_GAME_CODE ||
        info.id == GET_ROOM_STATE_CODE;
}

/* Handle any admin request */
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info) {

    switch (info.id) {

    case CLOSE_ROOM_CODE: return closeRoom(info);
    case START_GAME_CODE: return startGame(info);
    case GET_ROOM_STATE_CODE: return getRoomState(info);

    }

    return RequestResult { };   // Should never reach here but the compiler still complains
}

/* Client request to close a room */
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info) {
    
    try {
        /* Change the room state to closed, remove the admin and bring him back to the menu */
        m_room->setState(STATE::CLOSED);
        std::unique_lock<std::mutex> lock(this->adminLock);
        m_room->removeUser(this->m_user);
        lock.unlock();
        return { JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse
                { REQUEST_STATUS::SUCCESS }), this->m_factory.createMenuRequestHandler(this->m_user) };
    }
    catch (...) {
        return { JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse
                { REQUEST_STATUS::FAILURE }), nullptr };
    }
}

/* Client request to start their game */
RequestResult RoomAdminRequestHandler::startGame(RequestInfo info) {
    try {
        /* Set game state to started and bring them to the game screen */
        m_room->setState(STATE::STARTED);
        return { JsonResponsePacketSerializer::serializeResponse(StartGameResponse
                { REQUEST_STATUS::SUCCESS }), this->m_factory.createGameRequestHandler(this->m_user, this->m_factory.getGameManager()->createGame(*this->m_room)) };
    }
    catch (...) {
        return { JsonResponsePacketSerializer::serializeResponse(StartGameResponse
                   { REQUEST_STATUS::FAILURE }), nullptr };
    }
}

/* Client request to get the room state */
RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info) {

    try {
        /* Return all the room data */
        RoomData data = this->m_room->getData();
        return { JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse
                { REQUEST_STATUS::SUCCESS, data.name, data.isActive, this->m_room->getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion, data.maxPlayers }), nullptr };
    }
    catch (...) {
        return { JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse
                { REQUEST_STATUS::FAILURE }), nullptr };
    }
}