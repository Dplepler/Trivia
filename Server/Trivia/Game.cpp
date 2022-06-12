#include "Game.h"

Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players, unsigned int gameId) 
	: m_questions(questions), m_players(players), m_gameId(gameId) {  }

Question Game::getQuestionForUser(LoggedUser user) {

	try {
		unsigned int index = rand() % this->m_questions.size();
		this->m_players.at(user).currentQuestion = this->m_questions[index];

		this->m_questions.erase(std::next(this->m_questions.begin(), index));

		return this->m_players.at(user).currentQuestion;
	}
	catch (...) {
		std::cerr << "No user named" << user.getUsername() << std::endl;
	}
	return Question(QuestionDescriptor{});
}

void Game::submitAnswer(LoggedUser user, uint8_t answerId) {
	
	try {
		if (this->m_players.at(user).currentQuestion.getCorrectAnswerId() == answerId) {
			this->m_players.at(user).correctAnswerCount++;
		}
		else {
			this->m_players.at(user).wrongAnswerCount++;
		}
	}
	catch (...) {
		std::cerr << "No user named" << user.getUsername() << std::endl;
	}
}

void Game::removePlayer(LoggedUser user) {
	this->m_players.erase(user);
}

unsigned int Game::getId() {
	return this->m_gameId;
}