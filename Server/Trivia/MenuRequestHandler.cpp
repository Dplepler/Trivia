#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager& room, StatisticsManager& statistics) 
	: m_user(user), m_factory(factory), m_roomManager(room), m_statisticsManager(statistics) { }

bool MenuRequestHandler::isRequestRelevant(RequestInfo info) const { return true; }
RequestResult MenuRequestHandler::handleRequest(RequestInfo info) { return RequestResult(); }