#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data) {

	std::unique_lock<std::mutex> lock(this->m_roomLock);
	unsigned int id = this->m_rooms.size() ? this->m_rooms.end()->first + 1 : 0;	// Set new id

	/* Insert a new room */
	std::vector<LoggedUser> users;
	users.push_back(user);
	this->m_rooms.insert(std::pair<unsigned int, Room>(id, Room(data, users)));
	lock.unlock();
}

void RoomManager::deleteRoom(unsigned int id) {
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	this->m_rooms.erase(id);
	lock.unlock();
}

unsigned int RoomManager::getRoomState(unsigned int id) {
	
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	try {
		return this->m_rooms.at(id).getData().isActive;
	}
	catch (...) {
		throw std::exception("Invalid room ID");
	}
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