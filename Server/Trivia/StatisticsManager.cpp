#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) { }


std::vector<std::string> StatisticsManager::getHighScore() { 

	return std::vector<std::string>();
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