#pragma once
#include "SqliteDatabase.h"

#define TOP_PLAYERS_AMOUNT 5

#define SCORE(name) ((m_database->getNumOfCorrectAnswers(name) / m_database->getNumOfTotalAnswers(name)) * 10000 / m_database->getPlayerAverageAnswerTime(name))

class StatisticsManager {

public:

	StatisticsManager(IDatabase* database);
	~StatisticsManager() = default;

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);

private:

	IDatabase* m_database;

	std::string getHighestScoreName();

};