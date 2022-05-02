#pragma once
#include <iostream>

enum class RESPONSE {

	SIGNUP = 21,
	LOGIN,
	ERROR_RES = 40,

};

typedef struct LOGIN_RESPONSE_STRUCT {

	unsigned int status;

} LoginResponse;

typedef struct SIGNUP_RESPONSE_STRUCT {

	unsigned int status;

} SignupResponse;

typedef struct ERROR_RESPONSE_STRUCT {

	std::string message;

} ErrorResponse;