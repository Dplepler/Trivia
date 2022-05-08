#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) { }

unsigned int StatisticsManager::calcScore(std::string name) {
 return (this->m_database->getNumOfCorrectAnswers(name) / this->m_database->getNumOfTotalAnswers(name)) * SCORE_MULTIPLIER / this->m_database->getPlayerAverageAnswerTime(name);
}

std::string StatisticsManager::getHighestScoreName(std::vector<std::string> usernames) {
	
	unsigned int maxScore = 0;
	unsigned int score = 0;
	std::string username = "";
	size_t usernameAmount = usernames.size();

	for (unsigned int i = 0; i < usernameAmount; i++) {
		score = calcScore(usernames[i]);
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
		username = this->getHighestScoreName(allUsernames);
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