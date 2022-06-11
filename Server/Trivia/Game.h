#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include <map>

typedef struct GAME_DATA_STRUCT {

	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;

} GameData;

class Game {

public:

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answerId);
	void removePlayer(LoggedUser user);

private:

	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;



};