#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <random>
#include <io.h>


#define DB_NAME_SQLITE "TriviaDB.sqlite"



int userCallback(void* data, int argc, char** argv, char** azColName);
int questionCallback(void* data, int argc, char** argv, char** azColName);
int statsCallback(void* data, int argc, char** argv, char** azColName);



class SqliteDatabase : public IDatabase {


private:

	sqlite3* db;

	
	void setupDb();


public:


	SqliteDatabase();

	~SqliteDatabase();

	void addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) override;

	bool doesUserExist(std::string username) const override;

	bool doesPasswordMatch(std::string username, std::string password) const override;

	std::list<Question> getQuestions(int numOfQuestions) const override;

	float getPlayerAverageAnswerTime(std::string username) const override;

	int getNumOfCorrectAnswers(std::string username) const override;

	int getNumOfTotalAnswers(std::string username) const override;

	int getNumOfPlayerGames(std::string username) const override;

	std::vector<std::string> getAllUsernames() const override;


};