#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager& room, StatisticsManager& statistics) 
	: m_user(user), m_factory(factory), m_roomManager(room), m_statisticsManager(statistics) { }

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
    case CREATE_ROOM_CODE:        return RequestResult();
    case GET_ROOM_CODE:           return getRooms(info);
    case GET_ROOM_PLAYERS_CODE:   return RequestResult();
    case JOIN_ROOM_CODE:          return RequestResult();
    case GET_STATISTICS_CODE:     return getPersonalStats(info);
    case LOGOUT_REQUEST_CODE:     return signout(info);
  
  }
}

RequestResult MenuRequestHandler::signout(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info) {
  return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info) {
  return RequestResult();
}
