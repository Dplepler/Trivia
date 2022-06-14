#include "Game.h"

Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players, unsigned int gameId) 
	: m_questions(questions), m_players(players), m_gameId(gameId) {  }

Question Game::getQuestionForUser(LoggedUser user) {

	try {
		return this->m_questions[this->m_players.at(user).questionIndex++];
	}
	catch (...) {
		std::cerr << "No user named" << user.getUsername() << std::endl;
	}
}

void Game::submitAnswer(LoggedUser user, uint8_t answerId) {
	
	try {
		if (this->m_questions[this->m_players.at(user).questionIndex].getCorrectAnswerId() == answerId) {
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

GameData Game::getGameData(LoggedUser user) const {
	return this->m_players.at(user);
}

uint8_t Game::getCorrectAnswerIndex(LoggedUser user) const {
	return this->m_questions[this->m_players.at(user).questionIndex].getCorrectAnswerId();
}

std::map<LoggedUser, GameData> Game::getPlayers() const {
	return this->m_players;
}

void Game::removePlayer(LoggedUser user) {
	this->m_players.erase(user);
}

unsigned int Game::getId() {
	return this->m_gameId;
}