#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include <map>
#include <stdlib.h>

typedef struct GAME_DATA_STRUCT {

	unsigned int questionIndex;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;

} GameData;

class Game {

public:

	Game(std::vector<Question> questions, std::map<LoggedUser, GameData> players, unsigned int gameId);

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, uint8_t answerId, int ansTime);
	void removePlayer(LoggedUser user);
	
	std::map<LoggedUser, GameData> getPlayers() const;
	GameData getGameData(LoggedUser user) const;
	uint8_t getCorrectAnswerIndex(LoggedUser user) const;

	unsigned int getId();

private:

	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;

};