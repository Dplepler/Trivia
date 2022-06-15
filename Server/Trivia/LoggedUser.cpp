#include "LoggedUser.h"


/* Constructor */
LoggedUser::LoggedUser(std::string username): m_username(username)  { }


/* Getter */
std::string LoggedUser::getUsername() const { return m_username; }

/*		    Overloads        */
/*---------------------------*/
bool LoggedUser::operator==(LoggedUser otherUser) {
	return this->m_username == otherUser.m_username;
}

bool LoggedUser::operator<(LoggedUser otherUser) const {
	return this->m_username < otherUser.m_username;
}
/*---------------------------*/