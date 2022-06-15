#include "Question.h"

/* Constructor */
Question::Question(QuestionDescriptor question) {
	this->m_questionData = question;
}

/*		    Getters          */
/*---------------------------*/
std::string Question::getQuestion() const {
	return this->m_questionData.question;
}

std::vector<std::string> Question::getPossibleAnswers() const {
	return this->m_questionData.answers;
}

uint8_t Question::getCorrectAnswerId() const {
	return this->m_questionData.correctIndex;
}
/*---------------------------*/