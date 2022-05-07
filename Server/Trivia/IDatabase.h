#pragma once


#include <string>
#include <list>
#include <vector>
#include <stdint.h>



struct Question {

	std::string question;
	std::vector<std::string> answers;
	uint8_t correctIndex;
};




class IDatabase {

public:

	virtual bool doesUserExist(std::string username) const = 0;
	
	virtual bool doesPasswordMatch(std::string username, std::string password) const = 0;

	virtual void addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) = 0;

	virtual std::list<Question> getQuestions(int numOfQuestions) const = 0;

	virtual float getPlayerAverageAnswerTime(std::string username) const = 0;

	virtual int getNumOfCorrectAnswers(std::string username) const = 0;

	virtual int getNumOfTotalAnswers(std::string username) const = 0;

	virtual int getNumOfPlayerGames(std::string username) const = 0;

	virtual std::vector<std::string> getAllUsernames() const = 0;


};