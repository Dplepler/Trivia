#pragma once
#include "Game.h"
#include "Room.h"
#include "SqliteDatabase.h"
#include <map>

#define QUESTIONS_PER_GAME 15

class GameManager {

public:
	
	GameManager(IDatabase* database);

	Game createGame(Room room);
	void deleteGame(unsigned int gameId);

private:

	IDatabase* m_database;
	std::vector<Game> m_games;
	
};