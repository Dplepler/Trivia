#include "RoomManager.h"

/* Create a new room and add it to the room map */
void RoomManager::createRoom(LoggedUser user, RoomData data) {

	std::unique_lock<std::mutex> lock(this->m_roomLock);
	/* Insert a new room */
	std::vector<LoggedUser> users;
	users.push_back(user);
	m_rooms[data.id] = Room(data, users);	
	lock.unlock();
}

/* Delete a room and remove it from the room map */
void RoomManager::deleteRoom(unsigned int id) {
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	this->m_rooms.erase(id);
	lock.unlock();
}

/* Return the current state of the room */
STATE RoomManager::getRoomState(unsigned int id) {
	
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	STATE isActive;
	try {
		isActive = m_rooms.at(id).getData().isActive;
		lock.unlock();
		return isActive;
	}
	catch (...) {
		throw std::exception("Invalid room ID");
	}
}

/*		    Getters          */
/*---------------------------*/
Room* RoomManager::getRoom(unsigned int id) {	
	return &m_rooms[id];
}

std::vector<RoomData> RoomManager::getRooms() {

	std::vector<RoomData> rooms;
	size_t size = this->m_rooms.size();

	std::unique_lock<std::mutex> lock(this->m_roomLock);
	for (unsigned int i = 0; i < size; i++) {
		if (
			(m_rooms[i].getAllUsers().size() < m_rooms[i].getData().maxPlayers)
			&& m_rooms[i].getData().isActive == STATE::OPEN
			) {
			rooms.push_back(this->m_rooms[i].getData());
		}
	}

	lock.unlock();
	return rooms;
}
/*---------------------------*/

/* Add a user to a room */
void RoomManager::addUser(unsigned int id, LoggedUser newUser) {
	std::unique_lock<std::mutex> lock(this->m_roomLock);
	if(m_rooms[id].getAllUsers().size() < m_rooms[id].getData().maxPlayers) { m_rooms[id].addUser(newUser); }
	lock.unlock();
}


