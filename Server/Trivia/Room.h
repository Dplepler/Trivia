#pragma once
#include "LoginManager.h"

enum class STATE {

	OPEN,
	CLOSED,
	STARTED

};

typedef struct ROOM_DATA_STRUCT {

	std::string name;

	unsigned int id;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	STATE isActive;

} RoomData;



class Room {

public:

	Room() = default;
	Room(RoomData data, std::vector<LoggedUser> users);

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);

	void setState(STATE state);

	std::vector<std::string> getAllUsers() const;
	RoomData getData() const;

private:
	
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};