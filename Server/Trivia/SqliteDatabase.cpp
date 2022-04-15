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

	std::string insertQuery = "INSERT INTO Users\n(Username, Password, Email)\nVALUES(\n'" + newUsername + "', '" + newPassword + "', '" + newEmail + "');";
	char* errMsg = nullptr;

	// In cases where the user enters an epty string for any of the info, which should be considered invalid
	if (newUsername == "" || newPassword == "" || newEmail == "") { return; }

	int res = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errMsg);

	if(res != SQLITE_OK) {
		std::cerr << "Couldn't insert user info to the database" << std::endl << "New user was not created" << std::endl;
	}
}




bool SqliteDatabase::doesUserExist(std::string username) const {
	std::string selectQuery = "SELECT * FROM Users\nWHERE Username = '" + username + "';";
	char* errMsg = nullptr;
	SignupRequest userInfo { "", "", "" };

	int res = sqlite3_exec(db, selectQuery.c_str(), userCallback, &userInfo, &errMsg);

	if (res != SQLITE_OK) {
		std::cerr << "Could not complete operation" << std::endl;
		return false;
	}

	return (userInfo.username == username);
}




bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password) const {
	std::string selectQuery = "SELECT * FROM Users\nWHERE Username = '" + username + "';";
	char* errMsg = nullptr;
	SignupRequest userInfo{ "", "", "" };
	int res = sqlite3_exec(db, selectQuery.c_str(), userCallback, &userInfo, &errMsg);

	if (res != SQLITE_OK) {
		std::cerr << "Could not complete operation" << std::endl;
		return false;
	}

	return (userInfo.password == password);
}





int userCallback(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "Username") {
			((SignupRequest*)data)->username = argv[i];
		}
		else if (std::string(azColName[i]) == "Password") {
			((SignupRequest*)data)->password = argv[i];
		}
		else if (std::string(azColName[i]) == "Email") {
			((SignupRequest*)data)->email = argv[i];
		}
	}

	return 0;
}




SqliteDatabase::~SqliteDatabase() {

	sqlite3_close(db);
	db = nullptr;

}