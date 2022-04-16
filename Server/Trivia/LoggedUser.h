#pragma once



#include <string>



class LoggedUser {

private:

	std::string m_username;

public:

	LoggedUser(std::string username);

	std::string getUsername();

};
