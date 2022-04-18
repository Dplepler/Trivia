#pragma once



#include <string>



class LoggedUser {

public:

	LoggedUser(std::string username);

	std::string getUsername() const;

	bool operator==(LoggedUser otherUser);


private:

	std::string m_username;

};
