#pragma once
#include <string>
#include <vector>
#include "SqliteDatabase.h"

class Question {

public:

	Question(QuestionDescriptor question);
	Question() = default;
	~Question() = default;

	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	uint8_t getCorrectAnswerId() const;
	
private:

	QuestionDescriptor m_questionData;

};