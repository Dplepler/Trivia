#include "BaseRoomRequestHandler.h"



BaseRoomRequestHandler::BaseRoomRequestHandler(Room* room) {
    m_room = room;
}



RequestResult BaseRoomRequestHandler::getRoomState(RequestInfo info) {

    try {
        RoomData data = m_room->getData();
        return { JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse
                { REQUEST_STATUS::SUCCESS, data.name, data.isActive, m_room->getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion, data.maxPlayers }), nullptr };
    }
    catch (...) {
        std::cerr << "Error getting room state";
    }
}