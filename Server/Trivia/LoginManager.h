#pragma once


#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>


class LoginManager {


private:

	IDatabase* m_database;

	std::vector<LoggedUser> m_loggedUsers;



public:


	LoginManager(IDatabase* db);

	bool signup(std::string username, std::string password, std::string email);

	bool login(std::string username, std::string password);

	void logout(std::string username);



};