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

std::vector<std::string> Room::getAllUsers() const {

	size_t size = this->m_users.size();
	std::vector<std::string> users;

	for (unsigned int i = 0; i < size; i++) {
		users[i] = this->m_users[i].getUsername();
	}

	return users;
}

RoomData Room::getData() const {
	return this->m_metadata;
}