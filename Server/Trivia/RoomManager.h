#pragma once
#include "Room.h"
#include <map>

class RoomManager {

public:

	RoomManager() = default;
	
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(unsigned int id);
	STATE getRoomState(unsigned int id);

	void addUser(unsigned int id, LoggedUser newUser);

	std::vector<RoomData> getRooms();
	Room* getRoom(unsigned int id);

private:

	std::map<unsigned int, Room> m_rooms;
	std::mutex m_roomLock;
};