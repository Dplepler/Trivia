#include "StatisticsManager.h"

/* Constructor */
StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) { }

/* Calculate the scored based on our cool formula! ([[Correct answers / number of total answers] * 10000] / average answer time)*/
float StatisticsManager::calcScore(std::string name) {
	if (m_database->getNumOfTotalAnswers(name) == 0 || m_database->getPlayerAverageAnswerTime(name) == 0) { return 0; }
	return ((float)this->m_database->getNumOfCorrectAnswers(name) / (float)this->m_database->getNumOfTotalAnswers(name)) * SCORE_MULTIPLIER / this->m_database->getPlayerAverageAnswerTime(name);
}

/*		    Getters          */
/*---------------------------*/

/* Return the current best player */
std::string StatisticsManager::getHighestScoreName(std::vector<std::string> usernames) {
	
	if (!usernames.size()) { return ""; }

	float maxScore = calcScore(usernames[0]);
	std::string username = usernames[0];
	float score = 0;

	/* Iterate through all the scores and return the player name with the highest score */
	for (unsigned int i = 0; i < usernames.size(); i++) {
		score = calcScore(usernames[i]);
		if (score > maxScore) {
			maxScore = score;
			username = usernames[i];
		}	
	}
	
	return username;
}

/* Get all the top winners of the app */
std::vector<std::string> StatisticsManager::getHighScore() { 

	std::string username;
	std::vector<std::string> topPlayers {"", "", "", "", ""};

	std::vector<std::string> allUsernames = this->m_database->getAllUsernames();

	/* Iterate through all the users, each time find the best user and add it to our new least while removing it from the previous one */
	for (uint8_t i = 0; i < TOP_PLAYERS_AMOUNT; i++) {
		username = this->getHighestScoreName(allUsernames);
		topPlayers[i] = username;

		std::vector<std::string>::iterator it = std::find(allUsernames.begin(), allUsernames.end(), username);
		if (it != allUsernames.end()) { allUsernames.erase(it); }
	}

	return topPlayers;
}

/* Return the user statistics from the database */
std::vector<std::string> StatisticsManager::getUserStatistics(std::string username) {

	return std::vector<std::string>
		{
		std::to_string(this->m_database->getNumOfCorrectAnswers(username)),
		std::to_string(this->m_database->getNumOfPlayerGames(username)), 
		std::to_string(this->m_database->getNumOfTotalAnswers(username)),
		std::to_string(this->m_database->getPlayerAverageAnswerTime(username))
		};
}
/*---------------------------*/