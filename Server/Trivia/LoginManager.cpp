#include "LoginManager.h"



LoginManager::LoginManager(IDatabase* db): m_database(db) { }



// acceses db and inserts a new user record, thus creating an new account/user
bool LoginManager::signup(std::string username, std::string password, std::string email) {
	if (m_database->doesUserExist(username) || username.empty() || password.empty() || email.empty()) { return false; }
	m_database->addNewUser(username, password, email);
	m_loggedUsers.push_back(LoggedUser(username));
	return true;
}



// acceses db to validate login info of a user
bool LoginManager::login(std::string username, std::string password) {
	if (m_database->doesUserExist(username) && m_database->doesPasswordMatch(username, password)) {
		m_loggedUsers.push_back(LoggedUser(username));
		return true;
	}
	return false;
}



// removes a connected user out of the logged user vector by username, thus tops to track connection with im
void LoginManager::logout(std::string username) {
	bool foundUser = false;
	if (!m_database->doesUserExist(username)) { return; }
	for (int i = 0; i < m_loggedUsers.size() && !foundUser; i++) {
		if(m_loggedUsers[i].getUsername() == username) {
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
			foundUser = true;
		}
	}
}
