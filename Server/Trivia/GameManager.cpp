#include "GameManager.h"

/* Constructor */
GameManager::GameManager(IDatabase* database) {
	this->m_database = database;
}

/* Creates a new game and adds it to the game vector */
Game* GameManager::createGame(Room room) {

	std::map<LoggedUser, GameData> players;
	
	/* Make a player map from the room's user vector */
	for (unsigned int i = 0; i < room.getAllUsers().size(); i++) {
		players.insert(std::pair<LoggedUser, GameData>(room.getAllUsers()[i], GameData{ 0, 0, 0, 0 }));
	}

	std::list<QuestionDescriptor> questionDescs = this->m_database->getQuestions(room.getData().numOfQuestionsInGame);

	std::vector<Question> questions;

	for (auto& it : questionDescs) { questions.push_back(Question(it)); }	// Take all the questions
	
	// NOTE: The game's ID is the room's ID
	this->m_games.push_back(Game(questions, players, room.getData().id));	// Create a game using the questions and room players

	return &this->m_games.back();	// Return a pointer to the new game
}

/*		    Getters          */
/*---------------------------*/
Game* GameManager::getGame(unsigned int gameId) {

	for (auto& it : this->m_games) {
		if (it.getId() == gameId) { return &it; }
	}

	return nullptr;
}
/*---------------------------*/

/* Delete a game from the game vector */
void GameManager::deleteGame(unsigned int gameId) {

	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++) {
		if (it->getId() == gameId) {
			this->m_games.erase(it); return;	
		}
	}
}