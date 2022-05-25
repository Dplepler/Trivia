#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data) {

	std::unique_lock<std::mutex> lock(this->m_roomLock);
	/* Insert a new room */
	std::vector<LoggedUser> users;
	users.push_back(user);
	this->m_rooms.insert(std::pair<unsigned int, Room>(data.id, Room(data, users)));	
	lock.unlock();
}

void RoomManager::deleteRoom(unsigned int id) {
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	this->m_rooms.erase(id);
	lock.unlock();
}

unsigned int RoomManager::getRoomState(unsigned int id) {
	
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	unsigned int isActive = 0;
	try {
		isActive = m_rooms.at(id).getData().isActive;
		lock.unlock();
		return isActive;
	}
	catch (...) {
		throw std::exception("Invalid room ID");
	}
}

Room RoomManager::getRoom(unsigned int id) {	
	return this->m_rooms[id];
}


void RoomManager::addUser(unsigned int id, LoggedUser newUser) {
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	m_rooms[id].addUser(newUser);
	lock.unlock();
}


std::vector<RoomData> RoomManager::getRooms() {
	
	std::vector<RoomData> rooms;
	size_t size = this->m_rooms.size();

	std::unique_lock<std::mutex> lock(this->m_roomLock);
	for (unsigned int i = 0; i < size; i++) {
		rooms.push_back(this->m_rooms[i].getData());
	}

	lock.unlock();
	return rooms;
}
