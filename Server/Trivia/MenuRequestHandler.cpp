#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager)
	: m_user(user), m_factory(factory) {

  this->m_roomManager = roomManager;
 }

bool MenuRequestHandler::isRequestRelevant(RequestInfo info) const { 
  return info.id == CREATE_ROOM_CODE 
      || info.id == GET_ROOM_CODE 
      || info.id == GET_ROOM_PLAYERS_CODE 
      || info.id == JOIN_ROOM_CODE 
      || info.id == GET_STATISTICS_CODE 
      || info.id == LOGOUT_REQUEST_CODE;
 }

RequestResult MenuRequestHandler::handleRequest(RequestInfo info) { 

  switch (info.id) {
    case CREATE_ROOM_CODE:        return createRoom(info);
    case GET_ROOM_CODE:           return getRooms(info);
    case GET_ROOM_PLAYERS_CODE:   return getPlayersInRoom(info);
    case JOIN_ROOM_CODE:          return joinRoom(info);
    case GET_STATISTICS_CODE:     return getPersonalStats(info);
    case GET_HIGH_SCORE_CODE:     return getHighScore(info);
    case LOGOUT_REQUEST_CODE:     return signout(info);
  
  }
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info) {
  CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);

  std::unique_lock<std::mutex> lock(menuLock);
  unsigned int id = this->m_roomManager->getRooms().size() ? this->m_roomManager->getRooms().end()->id + 1 : 0;	// Set new id

  this->m_factory.getRoomManager()->createRoom(this->m_user, {request.roomName, id, request.maxUsers, request.questionCount, request.answerTimeout, true});

  return RequestResult{JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse{1}), this};
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::signout(RequestInfo info) {
  return RequestResult();
}

