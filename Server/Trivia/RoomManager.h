#pragma once
#include "Room.h"
#include <map>

class RoomManager {

public:

	RoomManager() = default;
	
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(unsigned int id);
	unsigned int getRoomState(unsigned int id);

	std::vector<RoomData> getRooms();

private:

	std::map<unsigned int, Room> m_rooms;
	std::mutex m_roomLock;
};