#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) { }

std::string StatisticsManager::getHighestScoreName() {
	
	unsigned int maxScore = 0;
	unsigned int score = 0;
	std::string username = "";
	std::vector<std::string> usernames = this->m_database->getAllUsernames();
	size_t usernameAmount = usernames.size();

	for (unsigned int i = 0; i < usernameAmount; i++) {
		score = SCORE(usernames[i]);
		if (score > maxScore) {
			maxScore = score;
			username = usernames[i];
		}	
	}
	
	return username;
}

std::vector<std::string> StatisticsManager::getHighScore() { 

	std::string username;
	std::vector<std::string> topPlayers;

	std::vector<std::string> allUsernames = this->m_database->getAllUsernames();;

	for (uint8_t i = 0; i < TOP_PLAYERS_AMOUNT; i++) {
		username = this->getHighestScoreName();
		if (username == "") { break; }
		topPlayers.push_back(username);

		std::vector<std::string>::iterator it = std::find(allUsernames.begin(), allUsernames.end(), username);
		if (it != allUsernames.end()) { allUsernames.erase(it); }
	}

	return topPlayers;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username) {

	return std::vector<std::string>
		{
		std::to_string(this->m_database->getNumOfCorrectAnswers(username)),
		std::to_string(this->m_database->getNumOfPlayerGames(username)), 
		std::to_string(this->m_database->getNumOfTotalAnswers(username)),
		std::to_string(this->m_database->getPlayerAverageAnswerTime(username))
		};
}