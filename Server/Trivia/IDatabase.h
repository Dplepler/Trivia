#pragma once


#include <string>



class IDatabase {

public:

	virtual bool doesUserExist(std::string username) const = 0;
	
	virtual bool doesPasswordMatch(std::string username, std::string password) const = 0;

	virtual void addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) = 0;


};