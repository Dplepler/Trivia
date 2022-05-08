#pragma once
#include "SqliteDatabase.h"

#define SCORE_MULTIPLIER 10000
#define TOP_PLAYERS_AMOUNT 5

class StatisticsManager {

public:

	StatisticsManager(IDatabase* database);
	~StatisticsManager() = default;

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);

private:

	IDatabase* m_database;

	std::string getHighestScoreName(std::vector<std::string> usernames);
	unsigned int calcScore(std::string name);

};