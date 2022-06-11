#pragma once
#include <iostream>
#include "Room.h"
#include <list>
#include <map>

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
	LEAVE_ROOM,
	SUBMIT,
	LEAVE_GAME,
	RESULTS,
	GET_QUESTIONS,
	
	ERROR_RES = 99,

};

typedef struct PLAYER_RESULT_STRUCT {

	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;

} PlayerResults;

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
	std::string name;
	STATE isActive;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
	unsigned int maxPlayers;

} GetRoomStateResponse;

typedef struct LEAVE_ROOM_RESPONSE_STRUCT {

	unsigned int status;

} LeaveRoomResponse;

typedef struct LEAVE_GAME_RESPONSE_STRUCT {

	unsigned int status;

} LeaveGameResponse;

typedef struct GET_QUESTION_RESPONSE_STRUCT {

	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;

} GetQuestionResponse;

typedef struct SUBMIT_ANSWER_RESPONSE {

	unsigned int status;
	unsigned int correctAnswerId;
	
} SubmitAnswerResponse;

typedef struct GET_GAME_RESULTS_RESPONSE_STRUCT {

	unsigned int status;
	std::vector<PlayerResults> results;
	
} GetGameResultsResponse;

