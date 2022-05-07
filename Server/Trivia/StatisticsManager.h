#pragma once
#include "SqliteDatabase.h"

class StatisticsManager {

public:

	StatisticsManager(IDatabase* database);
	~StatisticsManager() = default;

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);

private:

	IDatabase* m_database;

};