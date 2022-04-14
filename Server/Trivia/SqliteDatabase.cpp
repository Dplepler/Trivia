#include "SqliteDatabase.h"




SqliteDatabase::SqliteDatabase() {

	
	int dbExists = _access(DB_NAME_SQLITE, 0);

	int res = sqlite3_open(DB_NAME_SQLITE, &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
	}


	if (dbExists != 0) {
		// db init
	}
}



/* 
setup function for the database for when the database file is first created
It creates the following tables:
Users containing: Username(Text), Password(Text), Email(Text)
*/
void SqliteDatabase::setupDb() {

	std::string createQuery;
	char* errMsg;
	int queryRes = 0;

	// Users table creation
	createQuery = "CREATE TABLE Users (Username	TEXT, Password TEXT NOT NULL, Email	TEXT NOT NULL UNIQUE, PRIMARY KEY(Username))";
	queryRes = sqlite3_exec(db, createQuery.c_str(), nullptr, nullptr, &errMsg);

	if (queryRes != SQLITE_OK) {
		std::cerr << "An error has occured: " << errMsg << std::endl;
		_exit(1);
	}

}




SqliteDatabase::~SqliteDatabase() {

	sqlite3_close(db);
	db = nullptr;

}