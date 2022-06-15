#include "Game.h"

/* Constructor */
Game::Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players, unsigned int gameId) 
	: m_questions(questions), m_players(players), m_gameId(gameId) {  }

/* Gets a new question for a user upon client request, and increases the user's question index to the next one */
/* NOTE: The index only points to the logical question number, i.e question number 2 will be index 1 in the array */
Question Game::getQuestionForUser(LoggedUser user) {

	try {
		return this->m_questions[++this->m_players.at(user).questionIndex - 1];
	}
	catch (...) {
		std::cerr << "No user named" << user.getUsername() << std::endl;
	}
}

/* Submit a user's answer, if the answer was correct we increase the user's correct answers data, otherwise we increase their wrong answer data */
void Game::submitAnswer(LoggedUser user, uint8_t answerId) {
	
	try {
		if (this->m_questions[this->m_players.at(user).questionIndex - 1].getCorrectAnswerId() == answerId) {
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

/*		    Getters          */
/*---------------------------*/
GameData Game::getGameData(LoggedUser user) const {
	return this->m_players.at(user);
}

uint8_t Game::getCorrectAnswerIndex(LoggedUser user) const {
	return this->m_questions[this->m_players.at(user).questionIndex - 1].getCorrectAnswerId();
}

std::map<LoggedUser, GameData> Game::getPlayers() const {
	return this->m_players;
}

unsigned int Game::getId() {
	return this->m_gameId;
}
/*---------------------------*/

/* Removes a player from the player map */
void Game::removePlayer(LoggedUser user) {
	this->m_players.erase(user);
}
