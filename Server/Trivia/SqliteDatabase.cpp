#include "SqliteDatabase.h"




SqliteDatabase::SqliteDatabase() {

	
	int dbExists = _access(DB_NAME_SQLITE, 0);

	int res = sqlite3_open(DB_NAME_SQLITE, &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
	}


	if (dbExists != 0) {
		setupDb();
	}
}



/* 
setup function for the database for when the database file is first created
It creates the following tables:
Users containing: Username(Text), Password(Text), Email(Text)
*/
void SqliteDatabase::setupDb() {

	std::string createQuery;
	char* errMsg = nullptr;
	int queryRes = 0;

	// Users table creation
	createQuery = "CREATE TABLE Users (\nUsername TEXT,\nPassword TEXT NOT NULL,\nEmail TEXT NOT NULL UNIQUE,\nPRIMARY KEY(Username));";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}

}



// Inserts a new user to the DB with the provided and needed info (check Users table setup for more info)
void SqliteDatabase::addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) {

	std::string insertQuery = "INSERT INTO Users\n(Username, Password, Email)\nVALUES(\n'" + newUsername + "',\n" + newPassword + "',\n" + newEmail + "');";
	char* errMsg = nullptr;
	int res = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errMsg);

	if(res != SQLITE_OK) {
		std::cerr << "Couldn't insert user info to the database" << std::endl << "New user was not created" << std::endl;
		return;
	}
}



SqliteDatabase::~SqliteDatabase() {

	sqlite3_close(db);
	db = nullptr;

}