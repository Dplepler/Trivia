#include "Room.h"

Room::Room(RoomData data, std::vector<LoggedUser> users) : m_metadata(data), m_users(users) { }

void Room::addUser(LoggedUser user) {
	
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user) {
	
	for (auto it = this->m_users.begin(); it != m_users.end(); it++) {
		if (it->getUsername() == user.getUsername()) {
			m_users.erase(it); 
		}
	}
}

void Room::setState(STATE state) {
	this->m_metadata.isActive = state;
}

std::vector<std::string> Room::getAllUsers() const {

	std::vector<std::string> users;

	for (unsigned int i = 0; i < m_users.size(); i++) {
		users.push_back(this->m_users[i].getUsername());
	}

	return users;
}

RoomData Room::getData() const {
	return this->m_metadata;
}