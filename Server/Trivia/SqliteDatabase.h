#pragma once


#include "IDatabase.h"
#include "sqlite3.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <io.h>


#define DB_NAME_SQLITE "TriviaDB.sqlite"



int userCallback(void* data, int argc, char** argv, char** azColName);



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


};