#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(LoggedUser user, Game* game, GameManager* manager, RequestHandlerFactory& factory) 
	: m_user(user), m_game(game), m_gameManager(manager), m_factory(factory) { }

bool GameRequestHandler::isRequestRelevant(RequestInfo info) const { 

	return info.id == LEAVE_GAME_CODE ||
			info.id == GET_QUESTION_CODE ||
			info.id == SUBMIT_ANSWER_CODE ||
			info.id == GAME_RES_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info) { 

	switch (info.id) {

	case LEAVE_GAME_CODE:		return leaveGame(info);
	case GET_QUESTION_CODE:		return getQuestion(info);
	case SUBMIT_ANSWER_CODE:	return submitAnswer(info);
	case GAME_RES_CODE:			return getGameResult(info);	

	}

	return RequestResult { };
}

	

RequestResult GameRequestHandler::getQuestion(RequestInfo info) { 

	try {
		std::vector<std::string> answers = this->m_game->getQuestionForUser(this->m_user).getPossibleAnswers();
		std::map<unsigned int, std::string> ansMap;
		for (uint8_t i = 1; i < ANSWERS_PER_QUESTION + 1; i++) {
			ansMap.insert(std::pair<unsigned int, std::string>(i, answers[i - 1]));
		}

		return { JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse
				{ REQUEST_STATUS::SUCCESS, this->m_game->getQuestionForUser(this->m_user).getQuestion(), ansMap }), nullptr };
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse
				{ REQUEST_STATUS::FAILURE, "" }), nullptr };
	}
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info) { 

	try {
		SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);

		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::SUCCESS, request.answerId }), nullptr };

	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::FAILURE, 0 }), nullptr };
	}
}

RequestResult GameRequestHandler::getGameResult(RequestInfo info) { 
	
	try {
		std::vector<PlayerResults> players;
		std::map<LoggedUser, GameData> playerMap = this->m_game->getPlayers();
		for (auto& it : playerMap) {
			players.push_back(PlayerResults{ it.first.getUsername() , it.second.correctAnswerCount, it.second.wrongAnswerCount, it.second.averageAnswerTime });
		}
		GameData data = this->m_game->getGameData(this->m_user);
		return { JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse
				{ REQUEST_STATUS::SUCCESS, players }), nullptr };

	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::FAILURE, 0 }), nullptr };
	}

}

RequestResult GameRequestHandler::leaveGame(RequestInfo info) {

	try {
		return { JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse
						{ REQUEST_STATUS::SUCCESS }), this->m_factory.createMenuRequestHandler(this->m_user) };
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse
						{ REQUEST_STATUS::FAILURE }), nullptr };
	}

}