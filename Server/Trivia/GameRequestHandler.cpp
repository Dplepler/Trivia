#include "GameRequestHandler.h"

/* Constructor */
GameRequestHandler::GameRequestHandler(LoggedUser user, Game* game, GameManager* manager, RequestHandlerFactory& factory) 
	: m_user(user), m_game(game), m_gameManager(manager), m_factory(factory) { }

/* Check if the request is of one of the correct enum types */
bool GameRequestHandler::isRequestRelevant(RequestInfo info) const { 

	return info.id == LEAVE_GAME_CODE ||
			info.id == GET_QUESTION_CODE ||
			info.id == SUBMIT_ANSWER_CODE ||
			info.id == GAME_RES_CODE;
}

/* Check for any request that is relevant to a game */
RequestResult GameRequestHandler::handleRequest(RequestInfo info) { 

	switch (info.id) {

	case LEAVE_GAME_CODE:		return leaveGame(info);
	case GET_QUESTION_CODE:		return getQuestion(info);
	case SUBMIT_ANSWER_CODE:	return submitAnswer(info);
	case GAME_RES_CODE:			return getGameResult(info);	

	}

	return RequestResult { };	// Should never be reached (but the compiler still complains)
}

/* Client request to get a new question after previous question ended */
RequestResult GameRequestHandler::getQuestion(RequestInfo info) { 

	try {

		/* Serialize the question and the possible answers to send to user */
		Question question = this->m_game->getQuestionForUser(this->m_user);
		std::vector<std::string> answers = question.getPossibleAnswers();
		std::map<unsigned int, std::string> ansMap;
		for (uint8_t i = 1; i < ANSWERS_PER_QUESTION + 1; i++) {
			ansMap.insert(std::pair<unsigned int, std::string>(i, answers[i - 1]));
		}

		return { JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse
				{ REQUEST_STATUS::SUCCESS, question.getQuestion(), ansMap }), nullptr };
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse
				{ REQUEST_STATUS::FAILURE, "" }), nullptr };
	}
}

/* Client request to submit an answer for a given question */
RequestResult GameRequestHandler::submitAnswer(RequestInfo info) { 

	try {
		/* Deserialize the client's request and serialize a response containing the correct answer index */
		SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
		this->m_game->submitAnswer(this->m_user, request.answerId);

		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::SUCCESS, this->m_game->getCorrectAnswerIndex(this->m_user) }), nullptr };

	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::FAILURE, 0 }), nullptr };
	}
}

/* Client request to get the game results */
RequestResult GameRequestHandler::getGameResult(RequestInfo info) { 
	
	try {
		/* Serialize the player results into a vector */
		std::vector<PlayerResults> players;
		std::map<LoggedUser, GameData> playerMap = this->m_game->getPlayers();
		for (auto& it : playerMap) {
			players.push_back(PlayerResults{ it.first.getUsername() , it.second.correctAnswerCount, it.second.wrongAnswerCount, it.second.averageAnswerTime });
		}

		return { JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse
				{ REQUEST_STATUS::SUCCESS, players }), nullptr };

	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse
				{ REQUEST_STATUS::FAILURE, 0 }), nullptr };
	}

}

/* Client request to leave a game */
RequestResult GameRequestHandler::leaveGame(RequestInfo info) {

	try {
		/* Remove the player from the game and serialize a success message */
		std::unique_lock<std::mutex> lock(this->gameLock);
		this->m_game->removePlayer(this->m_user);
		lock.unlock();
		
		return { JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse
						{ REQUEST_STATUS::SUCCESS }), this->m_factory.createMenuRequestHandler(this->m_user) };
	}
	catch (...) {
		return { JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse
						{ REQUEST_STATUS::FAILURE }), nullptr };
	}

}