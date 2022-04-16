#include "LoginManager.h"



LoginManager::LoginManager(IDatabase* db): m_database(db) { }


bool LoginManager::signup(std::string username, std::string password, std::string email) {
	if (m_database->doesUserExist(username) || username.empty() || password.empty() || email.empty()) { return false; }
	m_database->addNewUser(username, password, email);
	m_loggedUsers.push_back(LoggedUser(username));
	return true;
}


bool LoginManager::login(std::string username, std::string password) {
	if (m_database->doesUserExist(username) && m_database->doesPasswordMatch(username, password)) {
		m_loggedUsers.push_back(LoggedUser(username));
		return true;
	}
	return false;
}


void logout(std::string username);
