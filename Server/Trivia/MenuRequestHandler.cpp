#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& factory, RoomManager* roomManager)
	: m_user(user), m_factory(factory) {

	this->m_roomManager = roomManager;

 }

bool MenuRequestHandler::isRequestRelevant(RequestInfo info) const { 
	return info.id == CREATE_ROOM_CODE 
		|| info.id == GET_ROOM_CODE 
		|| info.id == JOIN_ROOM_CODE 
		|| info.id == GET_STATISTICS_CODE 
		|| info.id == GET_HIGH_SCORE_CODE
		|| info.id == LOGOUT_REQUEST_CODE;
 }


RequestResult MenuRequestHandler::handleRequest(RequestInfo info) { 

	switch (info.id) {

	case CREATE_ROOM_CODE:			return createRoom(info);
	case GET_ROOM_CODE:				return getRooms(info);
	case JOIN_ROOM_CODE:			return joinRoom(info);
	case GET_STATISTICS_CODE:		return getPersonalStats(info);
	case GET_HIGH_SCORE_CODE:		return getHighScore(info);
	case LOGOUT_REQUEST_CODE:		return signout(info);
	
	}

	return RequestResult{ };
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info) {
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);

	unsigned int id = this->m_roomManager->getRooms().size() ? this->m_roomManager->getRooms().back().id + 1 : 0;	// Set new id

	this->m_factory.getRoomManager()->createRoom(this->m_user, {request.roomName, id, request.maxUsers, request.questionCount, request.answerTimeout, STATE::OPEN});

	return RequestResult{JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse{ REQUEST_STATUS::SUCCESS }), this->m_factory.createRoomAdminRequestHandler(this->m_user, m_roomManager->getRoom(id)) };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info) {
	return {JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse{REQUEST_STATUS::SUCCESS, this->m_factory.getRoomManager()->getRooms()}), nullptr};
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info) {
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);

	try {
		this->m_roomManager->addUser(request.roomId, m_user);
		return {JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse{REQUEST_STATUS::SUCCESS}), m_factory.createRoomMemberRequestHandler(m_user, m_roomManager->getRoom(request.roomId)) };
	}
	catch(...) {
		return { JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse{REQUEST_STATUS::FAILURE}), nullptr };
	}
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info) {
	
	try {
		return {JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse
				{REQUEST_STATUS::SUCCESS, this->m_factory.getStatisticsManager()->getUserStatistics(this->m_user.getUsername())}), nullptr};
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse
				{REQUEST_STATUS::FAILURE}), nullptr };
	}
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info) {

	try {
		return {JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse
				{REQUEST_STATUS::SUCCESS, this->m_factory.getStatisticsManager()->getHighScore()}), nullptr};
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse
				{REQUEST_STATUS::FAILURE}), nullptr };
	}
	
}

RequestResult MenuRequestHandler::signout(RequestInfo info) {
	try {
		m_factory.getLoginManager()->logout(m_user.getUsername());
		return {JsonResponsePacketSerializer::serializeResponse(LogoutResponse{REQUEST_STATUS::SUCCESS}), this->m_factory.createLoginRequestHandler()};
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(LogoutResponse{REQUEST_STATUS::FAILURE}), nullptr };
	}
}

