#pragma once


#include "IDatabase.h"



class SqliteDatabase : public IDatabase {


public:

	virtual bool doesUserExist(std::string username) const override;

	virtual bool doesPasswordMatch(std::string username, std::string password) const override;

	virtual void addNewUser(std::string newUsername, std::string newPassword, std::string newEmail) override;


};