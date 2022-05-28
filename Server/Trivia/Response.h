#pragma once
#include <iostream>
#include "Room.h"

enum class RESPONSE {

	SIGNUP = 21,
	LOGIN,
	LOGOUT,
	ROOMS,
	PLAYERS,
	HIGH_SCORE,
	STATS,
	JOIN,
	CREATE,
	
	ERROR_RES = 40,

}; 

typedef struct LOGIN_RESPONSE_STRUCT {

	unsigned int status;

} LoginResponse;

typedef struct SIGNUP_RESPONSE_STRUCT {

	unsigned int status;

} SignupResponse;

typedef struct LOGOUT_RESPONSE_STRUCT {
	
		unsigned int status;

} LogoutResponse;

typedef struct GET_ROOMS_RESPONSE_STRUCT {

	unsigned int status;
	std::vector<RoomData> rooms;

} GetRoomsResponse;

typedef struct GET_PLAYERS_IN_ROOMS_RESPONSE_STRUCT {

	std::vector<std::string> players;

} GetPlayersInRoomsResponse;

typedef struct GET_HIGH_SCORE_RESPONSE_STRUCT {
	
	unsigned int status;
	std::vector<std::string> statistics;

} GetHighScoreResponse;

typedef struct GET_PERSONAL_STATS_RESPONSE_STRUCT {

	unsigned int status;
	std::vector<std::string> statistics;

} GetPersonalStatsResponse;

typedef struct JOIN_ROOM_RESPONSE_STRUCT {

	unsigned int status;

} JoinRoomResponse;

typedef struct CREATE_ROOM_RESPONSE_STRUCT {

	unsigned int status;

} CreateRoomResponse;


typedef struct ERROR_RESPONSE_STRUCT {

	std::string message;

} ErrorResponse;