#pragma once


#include <string>
#include <list>
#include <vector>



struct Question {

	std::string question;
	std::vector<std::string> answers;
	int correctIndex;
};




class IDatabase {

public:

	virtual bool doesUserExist(std::string username) const = 0;
	
	virtual bool doesPasswordMatch(std::string username, std::string password) const = 0;

	virtual void addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) = 0;

	virtual std::list<Question> getQuestions(int numOfQuestions) = 0;


};