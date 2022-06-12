#include "GameManager.h"

GameManager::GameManager(IDatabase* database) {
	this->m_database = database;
}

Game GameManager::createGame(Room room) {

	std::map<LoggedUser, GameData> players;

	for (unsigned int i = 0; i < room.getAllUsers().size(); i++) {
		players.insert(std::pair<LoggedUser, GameData>(room.getAllUsers()[i], GameData{0, 0, 0, 0}));
	}

	std::list<QuestionDescriptor> questionDescs = this->m_database->getQuestions(room.getData().numOfQuestionsInGame);

	std::vector<Question> questions;

	for (auto& it : questionDescs) { questions.push_back(Question(it)); }

	this->m_games.push_back(Game(questions, players, room.getData().id));

	return this->m_games.back();
}

void GameManager::deleteGame(unsigned int gameId) {

	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++) {
		if (it->getId() == gameId) {
			this->m_games.erase(it); return;	
		}
	}
}