#include "LoginManager.h"



LoginManager::LoginManager(IDatabase* db): m_database(db) { }



// acceses db and inserts a new user record, thus creating an new account/user
bool LoginManager::signup(std::string username, std::string password, std::string email) {
	// locks to avoid multiple threads accessing db/adding a user to loggedUser vector
	std::unique_lock<std::mutex> loggedLock(m_loggedLock);
	if (m_database->doesUserExist(username) || username.empty() || password.empty() || email.empty()) { 
		loggedLock.unlock();
		return false; 
	}
	m_database->addNewUser(username, password, email);
	m_loggedUsers.push_back(LoggedUser(username));
	loggedLock.unlock();
	return true;
}



// acceses db to validate login info of a user
bool LoginManager::login(std::string username, std::string password) {
	bool loggedInSuccessfuly = false;
	// locks to avoid multiple threads accessing db/adding a user to loggedUser vector
	std::unique_lock<std::mutex> loggedLock(m_loggedLock);
	if (m_database->doesUserExist(username) && m_database->doesPasswordMatch(username, password)) {
		m_loggedUsers.push_back(LoggedUser(username));
		loggedInSuccessfuly = true;
	}
	loggedLock.unlock();
	return loggedInSuccessfuly;
}



// removes a connected user out of the logged user vector by username, thus tops to track connection with im
void LoginManager::logout(std::string username) {
	bool foundUser = false;
	// locks to avoid multiple threads accessing db/adding a user to loggedUser vector
	std::unique_lock<std::mutex> loggedLock(m_loggedLock);
	if (!m_database->doesUserExist(username)) { 
		loggedLock.unlock();
		return; 
	}
	for (int i = 0; i < m_loggedUsers.size() && !foundUser; i++) {
		if(m_loggedUsers[i].getUsername() == username) {
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
			foundUser = true;
		}
	}
	loggedLock.unlock();
}
