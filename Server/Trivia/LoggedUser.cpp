#include "LoggedUser.h"



LoggedUser::LoggedUser(std::string username): m_username(username)  { }



std::string LoggedUser::getUsername() const { return m_username; }
