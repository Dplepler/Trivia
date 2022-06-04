#pragma once
#include <iostream>
#include "Room.h"
#include <list>

enum class RESPONSE {

	SIGNUP = 21,
	LOGIN,
	LOGOUT,
	ROOMS,
	STATE,
	HIGH_SCORE,
	STATS,
	JOIN,
	CREATE,
	CLOSE,
	START,
	LEAVE,
	
	ERROR_RES = 99,

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

typedef struct CLOSE_ROOM_RESPONSE_STRUCT {

	unsigned int status;

} CloseRoomResponse;

typedef struct START_GAME_RESPONSE_STRUCT {

	unsigned int status;

}StartGameResponse;

typedef struct GET_ROOM_STATE_RESPONSE_STRUCT {

	unsigned int status;
	STATE isActive;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
	unsigned int maxPlayers;

} GetRoomStateResponse;

typedef struct LEAVE_ROOM_RESPONSE_STRUCT {

	unsigned int status;

} LeaveRoomResponse;