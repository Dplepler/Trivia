#pragma once
#include <string>
#include <vector>

class Question {

public:

	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;
	
private:

	std::string m_question;
	std::vector<std::string> m_possibleAnswers;

};